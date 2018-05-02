#include "kio.h"
#include "dev/acia.h"

void kput(char c) {
    acia_put(c);
}

void kprint(char *s) {
    while (*s != '\0')
        kput(*s++);
}

const char const hex[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

void kput_uint16(unsigned short n) {
    kput(hex[(n >> 12) & 0xF]);
    kput(hex[(n >> 8) & 0xF]);
    kput(hex[(n >> 4) & 0xF]);
    kput(hex[n & 0xF]);
}
