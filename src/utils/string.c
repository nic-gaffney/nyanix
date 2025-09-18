#include "string.h"

u32 strlen(char *str) {
    u32 size = 0;
    for (; (str[size]) != '\0'; size++)
        ;
    return size;
}

char *str_reverse(char *str) {
    char *str_ptr = str;
    u32 size = strlen(str);
    char return_str[size];

    // Reverse the string and store it in the temp
    for (u32 i = 0; i < size; i++)
        return_str[size - i - 1] = str[i];
    for (u32 i = 0; i < size; i++)
        *str_ptr++ = return_str[i];

    return str;
}

char *itoa(int num, char *buff, int base) {
    char *str_ptr = buff;
    if (num == 0) {
        buff[0] = '0';
        buff[1] = 0;
    }
    if (num < 0) {
        *str_ptr++ = '-';
        num *= -1;
    }
    while (num) {
        // If num % base is bigger than 9 (bigger base than 10), reach over to
        // the letters by adding 'A' - 10. Otherwise, add '0' to get the number
        // chars. Then set it to the current character and iterate the pointer
        *str_ptr++ = num % base + (num % base > 9 ? 'A' - 10 : '0');
        num /= base; // Next number
    }
    str_reverse(buff);
    return buff;
}
