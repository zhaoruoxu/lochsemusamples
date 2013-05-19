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
Format          db "%d,%s,%d", 0
Msg         db 0 dup(32)

.code 

Main proc
    invoke wsprintf, addr Msg, addr Format, 12, addr MsgBoxText, 23
    invoke MessageBox, NULL, addr Msg, addr MsgBoxCaption, MB_OK
    ret

Main endp

start: 

invoke Main
invoke ExitProcess, NULL 
end start