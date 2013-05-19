.586 
.model flat,stdcall 
option casemap:none 
include \masm32\include\windows.inc 
include \masm32\include\kernel32.inc 
;include \masm32\include\masm32rt.inc
include \masm32\include\msvcrt.inc
includelib \masm32\lib\msvcrt.lib
includelib \masm32\lib\kernel32.lib 
include \masm32\include\user32.inc 
includelib \masm32\lib\user32.lib
                     
.data 
szOkay  db "okay",13,10,0 

.code 
assume fs:nothing

start:
    push    offset Handler
    push    fs:[0]
    mov     fs:[0], esp
    xor     esi, esi
    
    ; exception here
    mov     eax, [esi]
    
X:
    invoke  crt_printf, offset szOkay
    
    pop     fs:[0]
    add     esp, 4
    
    inkey
    invoke ExitProcess, NULL 


Handler proc uses ebx pExcept:DWORD, pFrame:DWORD, pContext:DWORD, pDispatch:DWORD
    mov     eax, pContext
    ;invoke  crt_printf, offset szOkay
    assume  eax:ptr CONTEXT
    lea     ebx, X
    mov     [eax].regEip, ebx
    xor     eax, eax
    ret

Handler endp

    
end start