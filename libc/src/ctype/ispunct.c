#include <ctype.h>

int ispunct(int c) {
    if (c == EOF)
        return 0;
    else
        return '!' <= (unsigned char)c && (unsigned char)c <= '/' ||
               ':' <= (unsigned char)c && (unsigned char)c <= '@' ||
               '[' <= (unsigned char)c && (unsigned char)c <= '`' ||
               '{' <= (unsigned char)c && (unsigned char)c <= '~';
}
