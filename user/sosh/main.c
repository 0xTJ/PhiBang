#include <unistd.h>

const char rst_font[] = "\x1b[0m";
const char clear_screen[] = "\x1b[2J";
const char top_corner[] = "\x1b[H";

int main() {
    write(1, "TEST EXEC", 8);
    return 0;
}
