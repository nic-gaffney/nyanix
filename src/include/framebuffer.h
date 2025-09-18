#pragma once
// Width and height of the framebuffer
#include "types.h"
#include <stdarg.h>
#define FBWIDTH (80)
#define FBHEIGHT (25)
#define BUFFER_ADDR (0xb8000)
#define FB_PRINTK_BUFF_SIZE (FBWIDTH * FBHEIGHT)
#define GETCOLOR(FG, BG) (FG | BG << 4)

// Define colors for printing
enum u8 {
    FB_COLOR_BLACK = 0,
    FB_COLOR_BLUE = 1,
    FB_COLOR_GREEN = 2,
    FB_COLOR_CYAN = 3,
    FB_COLOR_RED = 4,
    FB_COLOR_MAGENTA = 5,
    FB_COLOR_BROWN = 6,
    FB_COLOR_LIGHT_GRAY = 7,
    FB_COLOR_DARK_GRAY = 8,
    FB_COLOR_LIGHT_BLUE = 9,
    FB_COLOR_LIGHT_GREEN = 10,
    FB_COLOR_LIGHT_CYAN = 11,
    FB_COLOR_LIGHT_RED = 12,
    FB_COLOR_PINK = 13,
    FB_COLOR_YELLOW = 14,
    FB_COLOR_WHITE = 15,
};

// Framebuffer character struct
struct FBchar {
    u8 character;
    u8 color;
};


// Prototypes
void initfb(void* fbaddr, u8 color);
void setColor(u8 fg, u8 bg);
u32 printk(const char *format, ...);
void putck(char c);
i32 putsk(char *str);
i32 formats(const char *format, char *buff, va_list args);
void cls();
