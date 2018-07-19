#include <string.h>
#include <unistd.h>

const char enter_at[] = "+++";
const char ex[] = "EX\r\n";
const char rh[] = "RH\r\n";
const char rd[] = "RD\r\n";

void setRemote(const char *host, const char *port) {
    for (int i = 0; i < 35000; ++i) {
        for (int i = 1000; i < 1500; ++i) {
            volatile int i = 0;
            i = 5;
        }
    }
    write(1, enter_at, sizeof(enter_at) - 1);
    for (int i = 0; i < 35000; ++i) {
        for (int i = 1000; i < 1500; ++i) {
            volatile int i = 0;
            i = 5;
        }
    }
    write(1, rh, sizeof(rh) - 1);
    write(1, host, strlen(host));
    write(1, enter_at, sizeof(enter_at) - 1);
    write(1, ex, sizeof(ex) - 1);
}
int main (int argc, char *argv[]) {
    (void) argc; (void) argv;

    setRemote("127.0.0.1", "0");

    return 0;
}
