#include <string.h>

void *memset(void *s, int c, size_t n) {
    size_t i = 0;
    while (i < n) {
        ((unsigned char *)s)[i] = (unsigned char)c;
        i++;
    }
}
