;:================================================
;: 0-Linux-nasm                        (c)Den,2019
;:
;: example of C-function in asm
;:
;: 1)nasm -f elf c_in_asm.asm
;: 2)gcc -m32 c_in_asm.o
;:================================================

section .code
global main

                        ;functions from libc
extern exit
extern puts
extern scanf
extern printf

main:
 
push dword msg
call puts               ;puts(msg)
sub esp, 4              ;stack cleaning
 
push dword a
push dword b
push dword msg1
call scanf              ;scanf(msg1, b, a)
sub esp, 12             ;stack cleaning
 
mov eax, dword [a]
add eax, dword [b]
 
push eax
push dword msg2
 
call printf             ;printf(msg2, a + b)
add esp, 8
 

push dword 0            ;Exit program with exit code 0
call exit
 
ret
 
 
msg  : db "An example:", 0xA, "write two num:",0xA,0
msg1 : db "%d%d",0
msg2 : db "sum = %d", 0xA, 0
 
section .bss
a resd 1
b resd 1