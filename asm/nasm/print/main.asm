;:================================================
;: 0-Linux-nasm                        (c)Den,2019
;:
;: example of function den_print in asm
;:
;: 1)for all files
;: nasm -f elf main.asm
;: 2)linking
;; ld -s -m elf_i386 main.o den_print.o print_bin.o 
;: print_hex.o print_str.o print_dec.o print_chr.o
;:================================================

section .code
extern den_print

global _start

_start:

    push 100
    push 3802
    push love
    push 'I'
    push Msg
    
    call den_print
   
    mov eax, 1         
    xor ebx, ebx
    int 0x80
    
section     .data
            
Msg:        db "%c %s %x %d %%!$"
love:       db "love$"