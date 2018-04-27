#include <string.h>

char *strcpy(char *restrict s1, const char *restrict s2) { // Optimize using asm
    while (*s2) {
        *s1++ = *s2++;
    }
    *s1 = *s2;
    return s1;
}
