#include <ctype.h>

int isblank(int c) {
    if (c == EOF)
        return 0;
    else
        return (unsigned char)c == ' ' || (unsigned char)c == '\t';
}
