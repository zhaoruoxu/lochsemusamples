.586 
.model flat,stdcall 
option casemap:none 
include \masm32\include\windows.inc 
include \masm32\include\kernel32.inc 
;include \masm32\include\masm32rt.inc
;include \masm32\include\msvcrt.inc
;includelib \masm32\lib\msvcrt.lib
includelib \masm32\lib\kernel32.lib 
include \masm32\include\user32.inc 
includelib \masm32\lib\user32.lib
                     
.data 
MsgBoxCaption  db "EmuTest0",0 
MsgBoxText       db "I'm not emulated",0
hModule     dd 0
FloatFmt       db "%f", 13, 10, 0
buf         db 64 dup(0)
f           dq 5.3

.code 

Main proc 
    finit
    fldpi
    fst qword ptr f
    
    invoke wsprintf, addr buf, offset FloatFmt, f
    ret
Main endp

start: 
;invoke GetModuleHandle, NULL
;mov hModule, eax
    invoke Main
    invoke MessageBox, NULL, addr buf, addr MsgBoxCaption, MB_OK 
    invoke ExitProcess, NULL 
end start