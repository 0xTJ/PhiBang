#include <ctype.h>

int isspace(int c) {
    if (c == EOF)
        return 0;
    else
        return (unsigned char)c == '\t' ||
               (unsigned char)c == '\n' ||
               (unsigned char)c == '\v' ||
               (unsigned char)c == '\f' ||
               (unsigned char)c == '\r' ||
               (unsigned char)c == ' ';
}
