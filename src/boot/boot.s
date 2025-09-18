section .text
extern kmain
global _start:function (_start.end - _start)
_start:
  mov esp, stack_top ; Initialize the stack
  cli
  [bits 32]
  push ebx
  push eax
  call kmain
  cli
.hang: hlt
  jmp .hang
.end:

section .bss ; allocate some space for the stack
align 16
stack_bottom:
resb 16384
stack_top:
