#include <string.h>

char *strcpy(char *restrict s1, const char *restrict s2) { // Optimize using asm
    do {
        *s1++ = *s2++;
    } while (*s2);
    return s1;
}
