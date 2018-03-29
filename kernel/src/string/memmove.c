#include <string.h>

void *memmove(void *s1, const void *s2, size_t n) {
    if (s1 < s2) {
        size_t i = 0;
        while (i < n) {
            ((unsigned char *)s1)[i] = ((unsigned char *)s2)[i];
            i++;
        }
    } else if (s2 < s1) {
        while (n > 0) {
            ((unsigned char *)s1)[n - 1] = ((unsigned char *)s2)[n - 1];
            n--;
        } 
    }
}
