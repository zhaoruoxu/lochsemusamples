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
hModule     dd 0
hHeap       dd INVALID_HANDLE_VALUE
lpMem       dd 0

.code 



start: 
invoke GetProcessHeap
mov hHeap, eax
invoke HeapAlloc, hHeap, HEAP_ZERO_MEMORY, 1000h
mov lpMem, eax
lea eax, lpMem
mov byte ptr[eax], 'h'
mov byte ptr[eax+1], 0
invoke MessageBox, NULL, offset lpMem, addr MsgBoxCaption, MB_OK 
invoke ExitProcess, NULL 
end start