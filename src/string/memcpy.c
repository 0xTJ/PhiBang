#include <string.h>

void *memcpy(void *s1, const void *s2, size_t n) {
    size_t i = 0;
    while (i < n) {
        ((char *)s1)[i] = ((char *)s2)[i];
        i++;
    }
}
