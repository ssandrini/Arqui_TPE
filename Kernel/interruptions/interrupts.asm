
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler
GLOBAL _exception0Handler


GLOBAL _int80Handler
GLOBAL _getKey
GLOBAL _RTC
GLOBAL _getRegisters

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN sysHandler

SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro



%macro exceptionHandler 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call exceptionDispatcher

	popState
	iretq
%endmacro


_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

haltcpu:
	cli
	hlt
	ret

_getKey:
	push rbp
    mov rbp, rsp
    mov rax,0

    in al, 0x60
       
    mov rsp, rbp
    pop rbp
    ret

_int80Handler:
	push rbp
	mov rbp, rsp
	
	mov rdx, rsi
	mov rsi, rdi
	mov rdi, rax
	
	call sysHandler
	sti

	mov rsp, rbp
	pop rbp
	ret

; en rdi viene el parametro que te permite elegir el dato del RTC
; 0 = sec
; 2 = min
; RTC(2)
_RTC:
	push rbp
	mov rbp, rsp
				
	mov rax, rdi
	out 70h, al
	in al, 71h

	mov rsp, rbp
	pop rbp
	ret

_getRegisters: ; vino la direccion del uint64 * en rdi
	push rbp
	mov rbp, rsp
	pushState
	mov rcx, 15  ; for(int i = 0 ; i< 15 ; i++)
	mov rax, 0 	 ; i
.loop: 
	pop rdx 
	mov [rdi+rax*8], rdx
	inc rax
	cmp rax, rcx
	je .end
	jmp .loop
.end:
	mov rsp, rbp
	pop rbp
	ret

SECTION .bss
	aux resq 1