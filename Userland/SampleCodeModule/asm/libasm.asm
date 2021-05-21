GLOBAL _write
GLOBAL _getBuffer
section .text

_write:
    push rbp
    mov rbp, rsp
                    ; en rdi estaria el caracter a imprimir (ya viene ahi desde la llamada)
    mov rax, 1     
    mov rsi, 0Fh   ; color
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


    
