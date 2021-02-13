#include "std.hpp"

int strlen(char *str) {
    int size = 0;
    while (*str++ != '\0') {
        size++;
    }
    return size;
}

int abs(int value) {
    if (value < 0) {
        return -value;
    } else {
        return value;
    }
}

void itoa(int value, char *str, int base) {
    char *low;
    if (base < 2 || base > 36) {
        *str = '\0';
        return;
    }
    if (value < 0 && base == 10) {
        *str = '-';
    }
    low = str;
    do {
        *str++ = "0123456789abcdefghijklmnopqrstuvwxyz"[abs(value) % base];
        value /= base;
    } while(value);
    *str-- = '\0';
    while (low < str) {
        char tmp = *low;
        *low++ = *str;
        *str-- = tmp;
    }
}

void *memcopy(char *dst, char *src, int n) {
    char *p = dst;
    while (n--) {
        *dst++ = *src++;
    }
    return p;
}
