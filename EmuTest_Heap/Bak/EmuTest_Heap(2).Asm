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
mov byte ptr[eax], 'h'
mov byte ptr[eax+1], 'e'
mov byte ptr[eax+2], 'l'
mov byte ptr[eax+3], 'l'
mov byte ptr[eax+4], 'o'

invoke MessageBox, NULL, addr lpMem, addr MsgBoxCaption, MB_OK 
invoke HeapFree, hHeap, 0, lpMem
invoke ExitProcess, NULL 
end start