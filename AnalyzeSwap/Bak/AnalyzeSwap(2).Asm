.586 
.model flat,stdcall 
option casemap:none 

include \masm32\include\masm32rt.inc

                     
.data 
    a dd 10
    b dd 20
    szFmt db 'a=%d b=%d', 13, 10, 0

.code 
assume fs:nothing

Swap proc uses ebx px:DWORD, py:DWORD
    LOCAL temp:DWORD
    
    ; temp = *px
    mov     eax, px
    mov     eax, [eax]
    mov     temp, eax
    
    ; *px = *py
    mov     eax, px
    mov     ebx, py
    mov     ebx, [ebx]
    mov     [eax], ebx
    
    ; *py = temp
    mov     eax, py
    mov     ebx, temp
    mov     [eax], ebx
    
    ret

Swap endp

Print proc
    
    invoke crt_printf, offset szFmt, a, b
    ret

Print endp

start:

    invoke Print
    invoke Swap, offset a, offset b
    invoke Print
    
    inkey
    invoke ExitProcess, NULL 
    

    
end start