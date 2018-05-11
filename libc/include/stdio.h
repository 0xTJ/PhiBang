#ifndef _INCLUDE_STDIO_H
#define _INCLUDE_STDIO_H

// typedef struct {
    // int fd;
    // int oflag;
    // int is_eof;
    // int is_err;
// } FILE;

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

// #define stderr (&_io_files[2])
// #define stdin (&_io_files[0])
// #define stdout (&_io_files[1])

// extern FILE _io_files[];

// int      fgetc(FILE *stream);
// char    *fgets(char *s, int n, FILE *stream);
// int      fputc(int c, FILE *stream);
// int      fputs(const char *restrict, FILE *restrict);

// #define getchar() fgetc(stdin)
// #define putchar(c) fputc(c, stdout)
// #define puts(s) fputs(s, stdout);

#endif
