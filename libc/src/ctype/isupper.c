#include <ctype.h>

int isupper(int c) {
    if (c == EOF)
        return 0;
    else
        return 'A' <= (unsigned char)c && (unsigned char)c <= 'Z';
}
