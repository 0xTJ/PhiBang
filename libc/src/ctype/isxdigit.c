#include <ctype.h>

int isxdigit(int c) {
    if (c == EOF)
        return 0;
    else
        return '0' <= (unsigned char)c && (unsigned char)c <= '9' ||
               'A' <= (unsigned char)c && (unsigned char)c <= 'F' ||
               'a' <= (unsigned char)c && (unsigned char)c <= 'f';
}
