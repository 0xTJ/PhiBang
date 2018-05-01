#include <ctype.h>

int isascii(int c) {
    return 0 <= c && c <= 0177;
}
