.386 
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
Format          db "%d,%d", 0


.code 

Main proc
    invoke GetCommandLine
    mov CmdLine, eax
    invoke MessageBox, NULL, CmdLine, addr MsgBoxCaption, MB_OK
    ret

Main endp

start: 

invoke Main
invoke ExitProcess, NULL 
end start