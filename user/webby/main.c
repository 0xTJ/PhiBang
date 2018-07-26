#include <string.h>
#include <unistd.h>

void delay(int num) {
    unsigned int i;
    for (; num > 0; --num)
        for (i = 0; i < 30000; ++i) {}
}

void setRemote(const char *host, const char *port) {
    delay(10);

    write(1, "RH", 2);
    write(1, host, strlen(host));
    write(1, "\r\n", 2);
    delay(10);

    write(1, "RP", 2);
    write(1, port, strlen(port));
    write(1, "\r\n", 2);
    delay(10);

    write(1, "SV\r\n", 4);
    delay(10);

    write(1, "RT\r\n", 4);
    delay(80);
}
int main (int argc, char *argv[]) {
    (void) argc; (void) argv;

    setRemote("127.0.0.1", "0");
    setRemote("www.google.com", "80");
    write(1, "EX\r\n", 4);
    delay(30);
    write(1, "dasfsdafdsafsd\r\n\r\ndasds\r\n\r\nfasds", sizeof("dasfsdafdsafsd\r\n\r\ndasds\r\n\r\nfasds") - 1);
    
    delay(20);
    write(1, "+++", 3);
    delay(20);
    
    setRemote("127.0.0.1", "0");


    return 0;
}
