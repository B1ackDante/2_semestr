;:================================================
;: 0-Linux-nasm                        (c)Den,2019
;:
;: 1)push num
;: result print num in hexadecimal system
;:
;: destroy: eax, ebx, ecx, edx, edi
;:================================================

section .bss
buffer resb 8

section .code
global print_hex

print_hex:                 
    push ebp               ;save ebp for recursion
    mov ebp, esp           ;save return address

    mov ecx, [ebp+8]       ;num

    mov edi, 8             ;destiation index

loop:
    mov eax, ecx     
    and eax, 0xf           ;eax = ecx mod 16
                   
    cmp al, 9              ;for print
    jle print_decimal_digit
print_hex_digit:           ;A..F
    sub al, 10
    add al, 'A'
    jmp print1
print_decimal_digit:       ;0..9
    add al, '0'
print1:
    dec edi
    mov byte [buffer+edi], al ;move symbol
    shr ecx, 4             ;ecx = ecx / 16
    jz  fret
    jmp loop
fret:
                           ;write (stdin, string_address, number_of_chars )
    mov eax, 4             ;write (system call number write = 4)
    mov ebx, 1             ;stdin (standard output stream handle = 1 )
    mov ecx, buffer        ;string_address
    mov edx, 8             ;number_of_shars
    int 80h          
    leave                  ;mov esp, ebp
                           ;pop ebp 
    ret                    ;pop IP 