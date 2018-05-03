#include <unistd.h>

const char test_str[] = "TEST EXEC\n";

int main() {
    write(1, test_str, sizeof(test_str));
    return 0;
}
