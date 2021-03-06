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
szOkay  db "not okay",13,10,0 
szInExcpt db "In exception handler", 13, 10, 0

.code 
assume fs:nothing

start:
    push    offset Handler
    push    fs:[0]
    mov     fs:[0], esp
    xor     esi, esi
    
    invoke crt_printf, offset szOkay
    
    ; exception here
    idiv    esi
    
X:
    invoke  crt_printf, offset szOkay
    
    pop     fs:[0]
    add     esp, 4
    
    inkey
    invoke ExitProcess, NULL 


Handler proc uses ebx pExcept:DWORD, pFrame:DWORD, pContext:DWORD, pDispatch:DWORD
    invoke  crt_printf, offset szInExcpt
    mov     eax, pContext
    assume  eax:ptr CONTEXT
    lea     ebx, X
    mov     [eax].regEip, ebx
    xor     eax, eax
    ret

Handler endp

    
end start