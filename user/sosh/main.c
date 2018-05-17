#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void getString(char *buffer, size_t sz) {
    size_t i = 0;
    uint8_t stop = 0;
    while (!stop) {
        int in = fgetc(stdin);
        switch (in) {
        case EOF:
            continue;
        case '\b':
            if (i > 0) {
                i--;
                fputs("\033[D\033[0K", stdout);
            }
            continue;
        case '\n':
            fputc('\n', stdout);
            stop = 1;
            break;
        default:
            if (i < sz - 1) {
                buffer[i++] = in;
                fputc(in, stdout);
            }
        }
    }
    buffer[i] = '\0';
}
int main (int argc, char *argv[]) {
    char line[65];
    argc;
    argv;
    fputs("> ", stdout);
    getString(line, 65);
    fputs(line, stdout);
    return 0;
}
