GLOBAL _write
GLOBAL _getBuffer
GLOBAL _getTime
GLOBAL _getReg
GLOBAL _getMem
GLOBAL _changeScreen
GLOBAL _quadratic
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

_quadratic:
    push rbp              ; armado del stackframe
    mov rbp, rsp
   
    fninit                
    fld   tword[rdi]      ; st0 = a
    fadd    st0           ; st0 = 2a
    fld   tword[rsi]      ; st0 = b   ; st1 = 2a
    fmul    st0           ; st0 = b²  ; st1 = 2a
    fld   tword[rdx]      ; st0 = c   ; st1 = b²  ;  st2 = 2a
    fmul    st2           ; st0 = 2ac ; st1 = b²  ;  st2 = 2a
    fadd    st0           ; st0 = 4ac ; st1 = b²  ;  st2 = 2a
    fsubp                 ; st0 = b²-4ac ; st1 = 2a
    ; tengo que chequear si st0 es menor que 0
    fldz                  ; st0 = 0.0 ; st1 = b²-4ac ; st2 = 2a

    ; al finalizar la comparacion me deja los flags en EFLAGS
    fcomip st0, st1       ; st0 = b²-4ac ; st1 = 2a
    ja .no_results        ; si es negativo
    ; si sigo aca es porque el discriminante era positivo
    fsqrt                 ; st0 = raiz de b²-4ac ; st1 = 2a
    
    ; calculo de la primera raiz
    fld    tword[rsi]     ; st0 = b   ; st1 = raiz de b²-4ac ; st2 = 2a
    fchs                  ; st0 = -b   ; st1 = raiz de b²-4ac ; st2 = 2a
    fsub    st1           ; st0 = -b - raiz de b²-4ac  ; st1 = raiz de b²-4ac ; st2 = 2a
    fdiv    st2           ; st0 = (-b - raiz de b²-4ac) / 2a  ; st1 = raiz de b²-4ac ; st2 = 2a
                          
    fstp    tword[rcx]    ; st0 = raiz de b²-4ac ; st1= 2a
    ;calculo de la segunda raiz
    fld    tword[rsi]     ; st0 = b   ; st1 = raiz de b²-4ac ; st2 = 2a
    fchs                  ; st0 = -b   ; st1 = raiz de b²-4ac ; st2 = 2a
    fadd    st1           ; st0 = -b + raiz de b²-4ac  ; st1 = raiz de b²-4ac ; st2 = 2a
    fdiv    st2           ; st0 = (-b + raiz de b²-4ac) / 2a  ; st1 = raiz de b²-4ac ; st2 = 2a
    fstp    tword[r8]     ; st0 = raiz de b²-4ac ; st1= 2a

    mov rax, 1            ; devulevo 1 porque pude calcular
    mov rsp, rbp
    pop rbp
    ret

.no_results:
    mov rax, 0            ; devulevo 0 porque no pude calcular
    mov rsp, rbp
    pop rbp
    ret
