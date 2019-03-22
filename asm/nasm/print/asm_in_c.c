{//======================================================
/**
  * 0-Linux-C                        (c)Den,2019
  *
  * example of function den_print(asm) in C
  *
  * 1)for all asm files
  * nasm -f elf den_print.asm
  * 2)gcc -c -m32 asm_in_c.c
  * 3)linking
  * gcc -m32 -o a.out asm_in_c.o den_print.o print_bin.o
  * print_hex.o print_str.o print_dec.o print_chr.o
  */
}//======================================================

#include <stdio.h>
extern void den_print(char* format_str, ...);
int main(void)
  {
    den_print("%c %s %x %d%%!%p$", 'I', "love$", 3802, 200);
    printf("\nGreat!");
  }
