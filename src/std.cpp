#include "std.h"

int strlen(char *string) {
    int size = 0;
    while (string[size] != '\0') size++;
    return size;
}

void reverse(char *string) {
    char c;
    for (int i = 0, j = strlen(string)-1; i < j; i++, j--) {
        c = string[i];
        string[i] = string[j];
        string[j] = c;
    }
}

void dec_int_to_char(char value, char *str_number) {
    int i = 0;
    do {
        str_number[i++] = value % 10 + '0';
    } while ((value /= 10) > 0);
    str_number[i] = '\0';
    reverse(str_number);
}

void *memcopy(char *dst, char *src, int n) {
    char *p = dst;
    while (n--) *dst++ = *src++;
    return p;
}
