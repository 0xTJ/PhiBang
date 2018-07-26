#include <string.h>
#include <unistd.h>

void delay(int num) {
    unsigned int i;
    for (; num > 0; --num)
        for (i = 0; i < 30000; ++i) {}
}

char req[] = "GET /websiteos/example_of_a_simple_html_page.htm HTTP/1.1\nHost: help.websiteos.com\n\n";

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

    setRemote("help.websiteos.com", "80");
    write(1, "EX\r\n", 4);
    delay(30);
    write(1, req, sizeof(req) - 1);
    delay(30);

    delay(20);
    write(1, "+++", 3);
    delay(20);
    
    setRemote("towel.blinkenlights.nl", "23");
    write(1, "EX\r\n", 4);
    while(1) {}
}
