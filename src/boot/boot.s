MAGIC equ 0xE85250D6 ; Lets bootloader find header*/
global .mboot ; Lets the linker find the multiboot header

section .bss ; allocate some space for the stack
align 16
stack_bottom:
resb 16384
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
  mov esp, stack_top ; Initialize the stack
  extern kmain
  call kmain
  cli
.hang: hlt
  jmp .hang
.end:
