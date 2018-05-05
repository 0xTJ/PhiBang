#include <stdio.h>
#include <unistd.h>

char *fgets(char *s, int n, FILE *stream) {
    size_t i = 0;
    char * ret = s;
    while (i < n - 1) {
        int res = fgetc(stream);
        if (res == '\n') {
            s[i++] = res;
            break;
        } else if (res == EOF) {
            stream->is_eof = EOF;
            ret = NULL;
            break;
        }
        s[i++] = res;
    }
    
    s[i] = '\0';
    return ret;
}
