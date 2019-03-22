;:================================================
;: 0-Linux-nasm                        (c)Den,2019
;:
;: 1)push num
;: 2)push number system
;: result print num in number system
;:
;: destroy: eax, ebx, ecx, edx, edi
;:================================================

section .bss
buffer resb 10

section .code
global print_dec

print_dec:

        push ebp                    ;save ebp for recursion
        mov ebp, esp                ;save return address

	mov ecx, [ebp + 12]          ;num

	mov ebx, [ebp + 8]         ;system number

        mov edi, NumLen
.loop:
	mov eax, ecx   
    	xor edx, edx               
    	div ebx                     ;ecx = ecx / 10 
    	mov ecx, eax

	add edx, '0'                ;for ASCII 
    	dec edi
    	mov byte [buffer + edi], dl
    	cmp ecx, 0
    	jne .loop

	mov eax, 4                  ;write( 1, buffer + edi, 19 - edi )
    	mov ebx, 1
    	lea ecx, [buffer + edi]
    	mov edx, NumLen
    	sub edx, edi
    	int 0x80

    	leave                       ;mov esp, ebp
                                    ;pop ebp 
    	ret                         ;pop IP               

NumLen  equ 10	

