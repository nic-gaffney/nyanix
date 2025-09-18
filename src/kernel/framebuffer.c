#include "framebuffer.h"
#include "string.h"
#include <stdarg.h>

struct FBchar *fb = (struct FBchar *)BUFFER_ADDR;
u8 fb_y = 0, fb_x = 0;

// u32 printk(const u8 *format, ...) {
//     va_list args;
//     va_start(args, format);
//     u8 buff[FB_PRINTK_BUFF_SIZE];
//     formats(format, buff, args);
//     va_end(args);
//     putsk(buff);
//     return strlen((const u8 *)buff);
// }

// void putck(u8 c);
// i32 putsk(u8 *str);
// i32 formats(const u8 *format, u8 *buff, va_list args);
