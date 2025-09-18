#pragma once

#include "types.h"
#define MB2_MAGIC 0xE85250D6
#define MB2_BOOT_MAGIC 0x36d76289 // Should be in EAX on boot
#define MB2_ARCH_I386 0
#define MB2_HEADER_LEN 16
#define MB2_TAG_END_SIZE 8
#define MB2_HEADER_TAG_FB 5
#define MB2_HEADER_TAG_OPT 1

typedef struct {
    u32 type;
    u32 size;
} mb2_tag;

typedef struct {
    u16 type;
    u16 flags;
    u32 size;
} mb2_tag_end;

typedef struct {
    u32 magic;
    u32 arch;
    u32 header_len;
    u32 checksum;
} mb2_header;

typedef struct {
    u32 type;
    u32 size;
    char *string;
} mb2_tag_command_line;

typedef struct {
    u16 type;
    u16 flags;
    u32 size;
    u32 console_flags;
} mb2_tag_flags;

typedef struct {
    u16 type;
    u16 flags;
    u32 size;
    u32 width;
    u32 height;
    u32 depth;
} mb2_tag_fb;

typedef struct {
    u32 type;
    u32 size;

    u64 framebuffer_addr;
    u32 framebuffer_pitch;
    u32 framebuffer_width;
    u32 framebuffer_height;
    u8 framebuffer_bpp;
#define MB2_FB_TYPE_INDEXED 0
#define MB2_FB_TYPE_RGB 1
#define MB2_FB_TYPE_EGA_TEXT 2
    u8 framebuffer_type;
    u16 reserved;
} mb2_tag_fbc;

typedef struct {
    u8 r;
    u8 b;
    u8 g;
} rgb_color;

typedef struct {
    mb2_tag_fbc common;
    union {
        struct {
            u16 fb_palette_num_colors;
            rgb_color fb_palette[0];
        };
        struct {
            u8 fb_red_field_position;
            u8 fb_red_mask_size;
            u8 fb_green_field_position;
            u8 fb_green_mask_size;
            u8 fb_blue_field_position;
            u8 fb_blue_mask_size;
        };
    };
} mb2_fb_info;
