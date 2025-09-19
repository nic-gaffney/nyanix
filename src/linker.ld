/* Tell the bootloader where the entrypoint is */
ENTRY(_start)
SECTIONS {
    /* 2M is a safe place to load, as it will be outside UEFI
     * and BIOS stuff. */
    . = 2M;

    .mb2 BLOCK(4K) : ALIGN(4K)
    {
        *(.mb2)
    }

    .text  BLOCK(4K) : ALIGN(4K)
    {
        *(.text)
    }

    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /* Read-write data (initialized) */
    .data BLOCK(4K) : ALIGN(4K)
    {
	    *(.data)
    }

    /* Read-write data (uninitialized) and stack */
    .bss BLOCK(4K) : ALIGN(4K)
    {
	    *(COMMON)
	    *(.bss)
    }

}
