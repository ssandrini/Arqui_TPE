GLOBAL _write
GLOBAL _getBuffer
GLOBAL _getTime
GLOBAL _getReg
GLOBAL _getMem
GLOBAL _changeScreen
section .text

_write:
    push rbp
    mov rbp, rsp
                    ; en rdi estaria el puntero a la string para imprimir
    mov rax, 1     
    mov rsi, 0Fh    ; color
    int 80h         ; llamada a la syscall write 

    mov rsp, rbp
    pop rbp
    ret

_getBuffer:
    push rbp
    mov rbp, rsp

    mov rax, 0     ; llamada a la syscall read
    int 80h
    
    mov rsp, rbp
    pop rbp
    ret

; void _getTime(int * fecha, int * hora);
_getTime:
    push rbp
    mov rbp, rsp

    mov rax, 2   ; llamada a la syscall time
    int 80h
    
    mov rsp, rbp
    pop rbp
    ret

; extern void _getReg(uint64_t registers);
_getReg:
    push rbp
    mov rbp, rsp

    mov rax, 3   ; llamada a la syscall getRegisters
    int 80h
    
    mov rsp, rbp
    pop rbp
    ret

_getMem:
    push rbp
    mov rbp, rsp

    mov rax, 4   ; llamada a la syscall getMemory
    int 80h
    
    mov rsp, rbp
    pop rbp
    ret

; en rdi se indica el numero de pantalla
_changeScreen:
    push rbp
    mov rbp, rsp

    mov rax, 5   ; llamada a la syscall changeScreen
    int 80h
    
    mov rsp, rbp
    pop rbp
    ret