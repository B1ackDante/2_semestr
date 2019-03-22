;:================================================
;: 0-Linux-nasm                        (c)Den,2019
;:
;: 1)push str address
;: result print string
;:
;: destroy: eax, ebx, ecx, edx
;:================================================

section .code
global print_str

print_str:
     push ebp                    ;save ebp for recursion
     mov ebp, esp                ;save return address
     
     mov ecx, [ebp + 8]          ;string adress
     
loop:
     mov al, [ecx]
     cmp al, '$'
     je exit
     
     mov eax, 4                  
     mov ebx, 1
     mov edx, 1
     int 0x80
     
     inc ecx
     
     jmp loop
     
exit:

    leave                       ;mov esp, ebp
                                ;pop ebp 
    ret                         ;pop IP   