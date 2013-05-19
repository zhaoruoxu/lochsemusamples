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
hInstance           dd 0
MsgBoxCaption       db "EmuDll1",0 
MsgProcessAttach    db "EmuDll1 - Process Attach", 0
MsgProcessDetach    db "EmuDll1 - Process Detach", 0
MsgThreadAttach     db "EmuDll1 - Thread Attach", 0
MsgThreadDetach     db "EmuDll1 - Thread Detach", 0
MsgTest             db "Why so serious?", 0


.code 

LibMain proc hInstDLL:DWORD, reason:DWORD, unused:DWORD
    
    .if reason == DLL_PROCESS_ATTACH
        invoke GetModuleHandle, NULL
        mov hInstance, eax
        invoke MessageBox, NULL, addr MsgProcessAttach, addr MsgBoxCaption, MB_OK or MB_ICONINFORMATION
        mov eax, TRUE
    .elseif reason == DLL_THREAD_ATTACH
        
    .elseif reason == DLL_THREAD_DETACH
    
    .elseif reason == DLL_PROCESS_DETACH
        invoke MessageBox, NULL, addr MsgProcessDetach, addr MsgBoxCaption, MB_OK or MB_ICONINFORMATION
        mov eax, TRUE
    .endif
    ret

LibMain endp

Junc1 proc lpMsg:DWORD, lpTitle:DWORD
    
    mov eax, addr MsgTest
    ret

Func1 endp

Junc2 proc
    
    invoke MessageBox, NULL, addr MsgTest, addr MsgBoxCaption, MB_OK
    ret

Func2 endp

end LibMain