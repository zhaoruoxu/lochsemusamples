.486 
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
MsgBoxCaption  db "EmuDllApp",0 
MsgBoxText       db "I'm not emulated",0


.code 


start: 
invoke Func1, addr MsgBoxText, addr MsgBoxCaption
invoke Func2
invoke Junc2
invoke ExitProcess, NULL 
end start