#ifndef _INCLUDE_STDIO_H
#define _INCLUDE_STDIO_H

typedef struct {
    int fd;
    int oflag;
    int is_eof;
    int is_err;
} FILE;

#ifndef _TYPEDEF_fpos_t
#define _TYPEDEF_fpos_t
typedef unsigned long fpos_t;
#endif

#ifndef _TYPEDEF_size_t
#define _TYPEDEF_size_t
typedef unsigned short size_t;
#endif

#ifndef _TYPEDEF_ssize_t
#define _TYPEDEF_ssize_t
typedef unsigned short ssize_t;
#endif

#define FILENAME_MAX (64)

#define FOPEN_MAX (8)

#ifndef EOF
#define EOF (-1)
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#define stderr (&_io_files[2])
#define stdin (&_io_files[0])
#define stdout (&_io_files[1])

extern FILE _io_files[];

int      feof(FILE *);
int      ferror(FILE *);
int      fgetc(FILE *);
int      fgetpos(FILE *restrict, fpos_t *restrict);
char    *fgets(char *restrict, int, FILE *restrict);
int      fileno(FILE *);
FILE    *fopen(const char *restrict, const char *restrict);
int      fputc(int, FILE *);
int      fputs(const char *restrict, FILE *restrict);
int      getc(FILE *);
#define  getc(stream) fgetc(stream)
int      getchar(void);
#define  getchar() getc(stdin)
char    *gets(char *);
#define  gets(s) fgets(s, 0b0111111111111111, stdin)
int      putc(int, FILE *);
#define  putc(stream) fputc(stream)
int      putchar(int);
#define  putchar(c) putc(c, stdout)
int      puts(const char *);
#define  puts(s) fputs(s, stdout)

#endif
