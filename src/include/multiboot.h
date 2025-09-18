#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include "types.h"
#define MB2_MAGIC 0xE85250D6
#define MB2_ARCH_I386 0
#define MB2_HEADER_LEN 16 // u32 * 4
#define MB2_END_TAG                                                            \
    (mb2_tag) { 0, 0, 8 }
#define MB2_NUM_TAGS 1
#define MB2_TAGS(...)                                                          \
    { __VA_ARGS__ }

typedef union mb2_tag_t {
    struct {
        u16 type;
        u16 flags;
        u32 size;
    } __attribute__((aligned(4))) end;
} mb2_tag;

static inline u32 mb2_tag_len(u32 len, mb2_tag *tags) {
    u32 size = 0;
    for (u32 i = 0; i < len; i++) {
        switch ((u16)tags[i].end.type) {
        case 0:
            size += 8;
        default:
            size += 0;
        }
    };
    return size;
}

struct mb2_header {
    u32 magic;
    u32 arch;
    u32 header_len;
    u32 checksum;
    mb2_tag tags[MB2_NUM_TAGS] __attribute__((aligned(4)));

} __attribute__((aligned(4)));

#endif // MULTIBOOT_H
