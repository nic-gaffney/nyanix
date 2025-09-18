#include "framebuffer.h"
#include "string.h"
#include <stdarg.h>
u8 fb_color = GETCOLOR(FB_COLOR_WHITE, FB_COLOR_BLACK);

inline void setColor(u8 fg, u8 bg) { fb_color = GETCOLOR(fg, bg); }

struct FBchar *fb = (struct FBchar *)BUFFER_ADDR;
u8 fb_y = 0, fb_x = 0;

void initfb(struct FBchar *addr, u8 color) {
    fb = addr;
    fb_color = color;
}

u32 printk(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buff[FB_PRINTK_BUFF_SIZE];
    formats(format, buff, args);
    va_end(args);
    putsk(buff);
    return strlen(buff);
}

i32 formats(const char *format, char *buff, va_list args) {
    i32 len = 0;
    i32 tmplen = 0;
    char *buffptr = buff;
    for (int i = 0; format[i] != '\0'; ++i) {
        if (format[i] == '%') {
            switch (format[++i]) {
            case 'i':
            case 'd':
                tmplen = strlen(itoa(va_arg(args, int), buffptr, 10));
                buffptr += tmplen;
                len += tmplen;
                break;
            case 'x':
                tmplen = strlen("0x");
                buffptr = "0x\0";
                buffptr += tmplen;
                len += tmplen;
                tmplen = strlen(itoa(va_arg(args, int), buffptr, 16));
                len += tmplen;
                buffptr += tmplen;
                break;
            case 's':
                buffptr = va_arg(args, char *);
                tmplen = strlen(buffptr);
                len += tmplen;
                buffptr += tmplen;
                break;
            case 'c':
                *buffptr = (va_arg(args, int));
                len++;
                buffptr += 1;
                break;
            case '%':
                *buffptr++ = '%';
                len++;
            case 'n':
                break;
            }
            continue;
        }
        *buffptr++ = format[i];
    }
    buffptr = 0;
    return len;
}

void clear_row(u32 row) {
    struct FBchar empty = (struct FBchar){
        ' ',
        fb_color,
    };

    // For every col in row, set vmem to empty
    for (u32 col = 0; col < FBWIDTH; col++) {
        fb[col + FBWIDTH * row] = empty;
    }
}

void print_newline() {
    fb_x = 0;
    if (fb_y < FBHEIGHT - 1) {
        fb_y++;
        return;
    }

    // If at bottom of screen, move all the text up one row
    for (u32 row = 1; row < FBHEIGHT; row++) {
        for (u32 col = 0; col < FBWIDTH; col++) {
            struct FBchar character = fb[col + FBWIDTH * row];
            fb[col + FBWIDTH * (row - 1)] = character;
        }
    }
}

void putck(char c) {
    // If \n, call newline
    if (c == '\n') {
        print_newline();
        return;
    }

    if (c == '\t') {
        putsk("    \0");
        return;
    }

    // if cols is too large, overflow
    if (fb_x >= FBWIDTH) {
        print_newline();
    }

    // set video memeory to requested character
    fb[fb_x + FBWIDTH * fb_y] = (struct FBchar){
        c,
        fb_color,
    };

    // iterate col
    fb_x++;
}

// print_str
int putsk(char *str) {
    // while character != '\0' print char
    u32 i;
    for (i = 0; str[i] != '\0'; ++i)
        putck(str[i]);
    return i;
}

// Call clear_row for every row
void cls() {
    for (u32 i = 0; i < FBHEIGHT; i++)
        clear_row(i);
    fb_x = 0;
    fb_y = 0;
}
