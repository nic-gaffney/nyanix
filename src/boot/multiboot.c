#include "multiboot.h"
#define TAGS MB2_TAGS(MB2_END_TAG)
#define HEADER_LEN                                                             \
    MB2_HEADER_LEN + mb2_tag_len(MB2_NUM_TAGS, (mb2_tag[MB2_NUM_TAGS])TAGS)

struct mb2_header mboot2 = (struct mb2_header){
    .magic = MB2_MAGIC,
    .arch = MB2_ARCH_I386,
    // Header
    .header_len = 16 + mb2_tag_len(1, (mb2_tag[1]){(mb2_tag){0, 0, 8}}),
    .checksum = -(MB2_MAGIC + MB2_ARCH_I386 + HEADER_LEN),
    .tags = TAGS,
};
