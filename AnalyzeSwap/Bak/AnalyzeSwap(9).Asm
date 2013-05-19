.586 
.model flat,stdcall 
option casemap:none 
include \masm32\include\windows.inc 
include \masm32\include\kernel32.inc 
include \masm32\include\masm32rt.inc
include \masm32\include\msvcrt.inc
includelib \masm32\lib\msvcrt.lib
includelib \masm32\lib\kernel32.lib 
include \masm32\include\user32.inc 
includelib \masm32\lib\user32.lib
                     
.data 
    a dd 10
    b dd 20

.code 
assume fs:nothing

Swap proc uses ebx ecx px:DWORD, py:DWORD
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



start:

    
    invoke ExitProcess, NULL 


    
end start