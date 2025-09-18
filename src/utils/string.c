#include "string.h"

u32 strlen(const u8 *str) {
    u32 size = 0;
    for (; (str[size]) != '\0'; size++)
        ;
    return size;
}
