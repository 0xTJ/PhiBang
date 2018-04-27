#include "kio.h"
#include "dev/acia.h"

void kput(char c) {
    acia_put(c);
}

void kprint(char *s) {
    while (*s != '\0')
        kput(*s++);
}
