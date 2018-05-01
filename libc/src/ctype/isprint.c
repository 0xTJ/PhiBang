#include <ctype.h>

int isprint(int c) {
    return isalnum(c) || ispunct(c) || isspace(c);
}
