#include "gdt.h"

GDT_entry gdt_create_entry(u32 base, u32 limit, u8 access, u8 flags){
    return (GDT_entry) {
            .base_high = base >> 24, // grabs bits 31-24
            .base_low = base >> 16,  // grabs bits 23-16
            .base_low_low = base,    // grabs bits 15-0
            .flags_limit_high = (flags << 4) | (limit >> 16),
            .access = access,
            .limit_low = limit
        };
}

u8 gdt_access_byte(_Bool present,
                   u8 privilege,
                   _Bool type,
                   _Bool executable,
                   _Bool direction_conforming,
                   _Bool read_write,
                   _Bool accessed) {
    return
        accessed
        | read_write << 1
        | direction_conforming << 2
        | executable << 3
        | type << 4
        | privilege << 6
        | present << 7;
}
