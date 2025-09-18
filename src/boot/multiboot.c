#include "multiboot.h"
const mb2_tag_end END = (mb2_tag_end){0, 0, 8};
const mb2_tag_fb MB2_FB = (mb2_tag_fb){
    .type = MB2_HEADER_TAG_FB,
    .flags = MB2_HEADER_TAG_OPT,
    .size = 20,
    .width = 1024,
    .height = 768,
    .depth = 32,
};
#define HEADER_LEN                                                             \
    MB2_HEADER_LEN                                                             \
    +END.size + MB2_FB.size

mb2_header mboot2 __attribute__((section(".mb2"))) = {
    .magic = MB2_MAGIC,
    .arch = MB2_ARCH_I386,
    .header_len = HEADER_LEN,
    .checksum = -(MB2_MAGIC + MB2_ARCH_I386 + HEADER_LEN),
};
mb2_tag_fb mb2_fb __attribute__((section(".mb2"))) = MB2_FB;
mb2_tag_end end __attribute__((section(".mb2"))) = END;
