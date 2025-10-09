#pragma once
#include "types.h"

typedef struct {
    u32 offset;
    u16 size;
} __attribute__((packed)) GDTR;

typedef struct {
    u8 base_high; // bits 24-31
    u8 flags_limit_high;
    u8 access;
    u8 base_low; // bits 16-23
    u16 base_low_low; // bits 0-15
    u16 limit_low;
} __attribute__((packed)) GDT_entry;

GDT_entry gdt_create_entry(u32 base, u32 limit, u8 access, u8 flags);
u8 gdt_access_byte(_Bool present,
                   u8 privilege,
                   _Bool type,
                   _Bool executable,
                   _Bool direction_conforming,
                   _Bool read_write,
                   _Bool accessed);

typedef GDT_entry* GDT;
