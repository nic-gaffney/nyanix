BITS 32

GRUB_MULTIBOOT_ARCHITECTURE_I386 equ 0
MULTIBOOT2_HEADER_MAGIC equ  0xe85250d6
MULTIBOOT2_BOOTLOADER_MAGIC equ  0x36d76289
MULTIBOOT_MOD_ALIGN equ  0x00001000
MULTIBOOT_INFO_ALIGN equ  0x00000008
MULTIBOOT_TAG_ALIGN equ  8
MULTIBOOT_TAG_TYPE_END equ  0
MULTIBOOT_TAG_TYPE_CMDLINE equ  1
MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME equ  2
MULTIBOOT_TAG_TYPE_MODULE equ  3
MULTIBOOT_TAG_TYPE_BASIC_MEMINFO equ  4
MULTIBOOT_TAG_TYPE_BOOTDEV equ  5
MULTIBOOT_TAG_TYPE_MMAP equ  6
MULTIBOOT_TAG_TYPE_VBE equ  7
MULTIBOOT_TAG_TYPE_FRAMEBUFFER equ  8
MULTIBOOT_TAG_TYPE_ELF_SECTIONS equ  9
MULTIBOOT_TAG_TYPE_APM equ  10
MULTIBOOT_TAG_TYPE_EFI32 equ  11
MULTIBOOT_TAG_TYPE_EFI64 equ  12
MULTIBOOT_TAG_TYPE_SMBIOS equ  13
MULTIBOOT_TAG_TYPE_ACPI_OLD equ  14
MULTIBOOT_TAG_TYPE_ACPI_NEW equ  15
MULTIBOOT_TAG_TYPE_NETWORK equ  16
MULTIBOOT_TAG_TYPE_EFI_MMAP equ  17
MULTIBOOT_TAG_TYPE_EFI_BS equ  18
MULTIBOOT_TAG_TYPE_EFI32_IH equ  19
MULTIBOOT_TAG_TYPE_EFI64_IH equ  20
MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR equ  21
MULTIBOOT_HEADER_TAG_END equ  0
MULTIBOOT_HEADER_TAG_INFORMATION_REQUEST equ  1
MULTIBOOT_HEADER_TAG_ADDRESS equ  2
MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS equ  3
MULTIBOOT_HEADER_TAG_CONSOLE_FLAGS equ  4
MULTIBOOT_HEADER_TAG_FRAMEBUFFER equ  5
MULTIBOOT_HEADER_TAG_MODULE_ALIGN equ  6
MULTIBOOT_HEADER_TAG_EFI_BS equ  7
MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI32 equ  8
MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI64 equ  9
MULTIBOOT_HEADER_TAG_RELOCATABLE equ  10
MULTIBOOT_ARCHITECTURE_I386 equ  0
MULTIBOOT_ARCHITECTURE_MIPS32 equ  4
MULTIBOOT_HEADER_TAG_OPTIONAL equ  1
MULTIBOOT_LOAD_PREFERENCE_NONE equ  0
MULTIBOOT_LOAD_PREFERENCE_LOW equ  1
MULTIBOOT_LOAD_PREFERENCE_HIGH equ  2
MULTIBOOT_CONSOLE_FLAGS_CONSOLE_REQUIRED equ  1
MULTIBOOT_CONSOLE_FLAGS_EGA_TEXT_SUPPORTED equ  2

section .mb2 align=4096
multiboot_header: ; Initial header
        dd MULTIBOOT2_HEADER_MAGIC
        dd GRUB_MULTIBOOT_ARCHITECTURE_I386
        dd multiboot_header_end - multiboot_header
        dd -(MULTIBOOT2_HEADER_MAGIC + GRUB_MULTIBOOT_ARCHITECTURE_I386 + (multiboot_header_end - multiboot_header))
; align 8
; flags_tag_start: ; Tell the system we need a console
;         dw MULTIBOOT_HEADER_TAG_CONSOLE_FLAGS
;         dw MULTIBOOT_HEADER_TAG_OPTIONAL
;         dd flags_tag_end - flags_tag_start
;         dd MULTIBOOT_CONSOLE_FLAGS_EGA_TEXT_SUPPORTED
; flags_tag_end:
align 8
entry_address_tag_start: ;
        dw MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS
        dw MULTIBOOT_HEADER_TAG_OPTIONAL
        dd entry_address_tag_end - entry_address_tag_start ; This is 0xc
        dd _start
entry_address_tag_end:
; align 8
; framebuffer_tag_start:
;         dw MULTIBOOT_HEADER_TAG_FRAMEBUFFER
;         dw MULTIBOOT_HEADER_TAG_OPTIONAL
;         dd framebuffer_tag_end - framebuffer_tag_start
;         dd 1024
;         dd 768
;         dd 32
; framebuffer_tag_end:

align 8
        dw MULTIBOOT_HEADER_TAG_END
        dw 0
        dd 8
multiboot_header_end:

section .bss ; allocate some space for the stack
align 32
stack_bottom:
resb 16384
stack_top:



section .text
extern kmain
global _start:function (_start.end - _start)
_start:
  mov esp, stack_top ; Initialize the stack
  mov ebp, stack_top
  push $0
  popf
  push ebx ; push multiboot 2 information
  push eax ; push address
  call kmain
  cli
.hang: hlt
  jmp .hang
.end:
