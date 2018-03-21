#include <stdio.h>

const char rst_font[] = "\x1b[0m";
const char clear_screen[] = "\x1b[2J";
const char top_corner[] = "\x1b[H";

void sosh_main() {
    int c;
    puts(rst_font);
    puts(clear_screen);
    puts(top_corner);
    puts("> ");
    do {
        c = getchar();
        putchar(c);
    } while (c != '\n');
}
