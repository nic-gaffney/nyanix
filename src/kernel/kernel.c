#include "framebuffer.h"
#include "multiboot.h"
#include "types.h"
#include <stdint.h>

void kmain(u64 mb2_magic, u64 addr) {
    mb2_tag *tag;
    u32 size;

    ((struct FBchar *)0xB8000)[1] =
        (struct FBchar){'5', GETCOLOR(FB_COLOR_WHITE, FB_COLOR_BLACK)};

    initfb((void *)0xb8000, GETCOLOR(FB_COLOR_WHITE, FB_COLOR_BLACK));
    printk("Hello World!");
    ((struct FBchar *)0xB8000)[1] =
        (struct FBchar){'5', GETCOLOR(FB_COLOR_WHITE, FB_COLOR_BLACK)};

    if (mb2_magic != MB2_BOOT_MAGIC) {
        printk("Invalid magic number: %x\n", (u32)mb2_magic);
        return;
    }
    if (addr & 7) {
        printk("Unaligned mbi: %x\n", addr);
        return;
    }

    size = *(u32 *)addr;
    tag = (mb2_tag *)addr + 8; // moves to the first tag

    {
        u32 color;
        unsigned i;
        mb2_fb_info *tagfb = (mb2_fb_info *)tag;
        void *fb = (void *)(unsigned long)tagfb->common.framebuffer_addr;

        switch (tagfb->common.framebuffer_type) {
        case MB2_FB_TYPE_INDEXED: {
            unsigned best_distance, distance;
            rgb_color *palette;

            palette = tagfb->fb_palette;

            color = 0;
            best_distance = 4 * 256 * 256;

            for (i = 0; i < tagfb->fb_palette_num_colors; i++) {
                distance = (0xff - palette[i].b) * (0xff - palette[i].b) +
                           palette[i].r * palette[i].r +
                           palette[i].g * palette[i].g;
                if (distance < best_distance) {
                    color = i;
                    best_distance = distance;
                }
            }
        } break;

        case MB2_FB_TYPE_RGB:
            color = ((1 << tagfb->fb_blue_mask_size) - 1)
                    << tagfb->fb_blue_field_position;
            break;

        case MB2_FB_TYPE_EGA_TEXT:
            color = '\\' | 0x0100;
            break;

        default:
            color = 0xffffffff;
            break;
        }

        for (i = 0; i < tagfb->common.framebuffer_width &&
                    i < tagfb->common.framebuffer_height;
             i++) {
            switch (tagfb->common.framebuffer_bpp) {
            case 8: {
                u8 *pixel = fb + tagfb->common.framebuffer_pitch * i + i;
                *pixel = color;
            } break;
            case 15:
            case 16: {
                u16 *pixel = fb + tagfb->common.framebuffer_pitch * i + 2 * i;
                *pixel = color;
            } break;
            case 24: {
                u32 *pixel = fb + tagfb->common.framebuffer_pitch * i + 3 * i;
                *pixel = (color & 0xffffff) | (*pixel & 0xff000000);
            } break;

            case 32: {
                u32 *pixel = fb + tagfb->common.framebuffer_pitch * i + 4 * i;
                *pixel = color;
            } break;
            }
        }
    }

    printk("Size: %x\n", size);
    while (1)
        ; /* do nothin */
}
