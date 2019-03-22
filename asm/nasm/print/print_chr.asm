;:================================================
;: 0-Linux-nasm                        (c)Den,2019
;:
;: 1)push char
;: result print char
;:
;: destroy: eax, ebx, ecx, edx
;:================================================

section .code
global print_chr

print_chr:
     push ebp                    ;save ebp for recursion
     mov ebp, esp                ;save return address
     
     lea ecx, [ebp + 8]          ;symb adress
     
     mov eax, 4                  
     mov ebx, 1
     mov edx, 1
     int 0x80

     leave                       ;mov esp, ebp
                                 ;pop ebp 
     ret                         ;pop IP   