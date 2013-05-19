.586 
.model flat,stdcall 
option casemap:none 

include \masm32\include\masm32rt.inc

                     
.data 
    v   dd 10
    res dd 0
    szFmt db '%d! = %d', 13, 10, 0
.code 
assume fs:nothing

Factorial proc n:dword, p:dword
    mov     ecx, n
    mov     eax, 1
    xor     edx, edx
L_CALC:
    imul    ecx
    loop    L_CALC
    
    mov     edx, p
    mov     [edx], eax
    
    ret

Factorial endp

Print proc
    
    invoke crt_printf, offset szFmt, v, res
    ret

Print endp

start:

    ;invoke Print
    invoke Factorial, v, offset res
    invoke Print
    
    ;inkey
    invoke ExitProcess, NULL 
    

    
end start