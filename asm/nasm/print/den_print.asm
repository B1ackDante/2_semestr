;:================================================
;: Linux- Den_print()                  (c)Den,2019
;:
;: 1)push format str arguments
;: 2)push format str address
;: result print string with arguments
;:
;: destroy: eax, ebx, ecx, edx, esi
;:================================================

section .code
global den_print

extern print_dec
extern print_bin
extern print_hex
extern print_str
extern print_chr

den_print:
    pop esi
    push 0
    push 0
    push 0
    push esi

    push ebx
    push ebp               ;save ebp for recursion
    mov ebp, esp           ;save return address
    lea esp, [ebp + 24]
    
    pop esi                ;string adress
    
print_symb:

    mov al, [esi]
    
    cmp al, '$'
    je exit
    
    cmp al, '%'
    je switch
    
                           ;write (stdin, string_address, number_of_chars )
    mov eax, 4             ;write (system call number write = 4)
    mov ebx, 1             ;stdin (standard output stream handle = 1 )
    mov ecx, esi           ;string_address
    mov edx, 1             ;number_of_shars
    int 80h
    
    inc esi
    
    jmp print_symb
    
switch:
    inc esi

    lodsb		  ;mov al, [si] inc si
    
bin:
    cmp al, 'b'
    jne hex

    call print_bin
    
    add esp, 4    
    jmp print_symb
hex:
    cmp al, 'x'
    jne decm

    call print_hex
    
    add esp, 4    
    jmp print_symb
decm:
    cmp al, 'd'
    jne oct

    push 10
    call print_dec
    
    add esp, 8    
    jmp print_symb
oct:
    cmp al, 'o'
    jne string

    push 8
    call print_dec
     
    add esp, 8   
    jmp print_symb
string:
    cmp al, 's'
    jne char
    
    call print_str
    
    add esp, 4
    jmp print_symb
char:
    cmp al, 'c'
    jne percent
    
    call print_chr
    
    add esp, 4
    jmp print_symb
percent:
    cmp al, '%'
    jne print_symb
    
    mov eax, 4             ;write (system call number write = 4)
    mov ebx, 1             ;stdin (standard output stream handle = 1 )
    mov ecx, perc          ;string_address
    mov edx, 1             ;number_of_shars
    int 80h
    
    jmp print_symb
        
exit:
    leave                  ;mov esp, ebp
                           ;pop ebp 
    pop ebx
    ret                    ;pop IP               

perc:        db '%'        
        
          