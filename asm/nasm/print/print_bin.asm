;:================================================
;: 0-Linux-nasm                        (c)Den,2019
;:
;: 1)push num
;: result print num in binary system
;:
;: destroy: eax, ebx, ecx, edx, edi
;:================================================

section .bss
buffer resb 32

section .code
global print_bin

print_bin:

        push ebp                    ;save ebp for recursion
        mov ebp, esp                ;save return address
        
        mov edx, [ebp + 8]          ;num
        
        mov edi, NumLen
        
loop:

        shr edx, 1		   ;div 2, remain to flag c
        dec edi
	jc set_1
	jmp set_0
set_1:	
	mov byte [buffer + edi], '1'
        jmp then
set_0:
	mov byte [buffer + edi], '0'
then:
        cmp edx, 0
        jne loop
        
        mov eax, 4                  ;write( 1, buffer + edi, 19 - edi )
        mov ebx, 1
        lea ecx, [buffer + edi]
        mov edx, NumLen
        sub edx, edi
        int 0x80
        
    	leave                       ;mov esp, ebp
                                    ;pop ebp 
    	ret                         ;pop IP               

NumLen  equ 32