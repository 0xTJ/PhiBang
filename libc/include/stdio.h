#ifndef _INCLUDE_STDIO_H
#define _INCLUDE_STDIO_H

enum _io_mode { _MODE_NONE, _MODE_READ, _MODE_WRITE, _MODE_READ_WRITE };

extern int get(int fd);
extern void put(int fd, int c);

#define EOF (-1)

typedef struct {
    int fd;
    enum _io_mode mode;
    int is_eof;
    int is_err;
} FILE;

#define FOPEN_MAX (8)

#define stderr (&(_io_files[2])
#define stdin (&_io_files[0])
#define stdout (&_io_files[1])

extern FILE _io_files[];

void _setup_stdio();

int fgetc(FILE *stream);
char *fgets(char *s, int n, FILE *stream);
int fputc(int c, FILE *stream);
int fputs(const char *s, FILE *stream);

#define getchar() fgetc(stdin)
#define putchar() fputc(stdout)

#endif
