#include <unistd.h>
#include <stdint.h>
#include <string.h>

short test;

void getString(char *buffer, size_t sz) {
    size_t i = 0;
    uint8_t stop = 0;
    while (!stop) {
        char in;
        if (read(0, &in, 1) < 1)
            continue;
        switch (in) {
        case '\b':
            if (i > 0) {
                i--;
                write(1, "\033[D\033[0K", sizeof("\033[D\033[0K") - 1);
            }
            continue;
        case '\n':
            write(1, "\n", 1);
            stop = 1;
            break;
        default:
            if (i < sz - 1) {
                buffer[i++] = in;
                write(1, &in, 1);
            }
        }
    }
    buffer[i] = '\0';
}
int main (int argc, char *argv[]) {
    char line[65];
    argc;
    argv;
    write(1, "Enter .drl size", sizeof());
    getString(line, 65);
    int length = 0;
    for (int i = 0; line[i]; ++i)
        length = length * 10 + line[i];
    malloc(
    return 0;
}
