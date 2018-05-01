#include <ctype.h>

int isgraph(int c) {
    return isalnum(c) || ispunct(c);
}
