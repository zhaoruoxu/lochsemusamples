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
MsgBoxText       db "Hello LochsEmu",0
hModule     dd 0

.code 
start: 
invoke GetModuleHandle, NULL
mov hModule, eax
invoke MessageBox, NULL, addr MsgBoxText, addr MsgBoxCaption, MB_OK 
invoke ExitProcess, NULL 
end start