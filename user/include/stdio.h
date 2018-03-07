#ifndef _INCLUDE_STDIO_H
#define _INCLUDE_STDIO_H

/* #include <stdarg.h> */


/* TYPES */

#ifndef _TYPEDEF_SIZE_T
typedef unsigned short int size_t;
#define _TYPEDEF_SIZE_T
#endif

#ifndef _TYPEDEF_FPOS_T
typedef unsigned int fpos_t;
#define _TYPEDEF_FPOS_T
#endif

#ifndef _TYPEDEF_FILE
typedef struct {
    int fd;
    fpos_t fpos;
    unsigned char *buf;
    int err_ind;
    int eof_ind;
} FILE;
#define _TYPEDEF_FILE
#endif


/* MACROS */

#ifndef NULL
#define NULL (0)
#endif

#ifndef _IOFBF
#define _IOFBF (1)
#endif

#ifndef _IOLBF
#define _IOLBF (2)
#endif

#ifndef _IONBF
#define _IONBF (3)
#endif

#ifndef BUFSIZ
#define BUFSIZ (256)
#endif

#ifndef EOF
#define EOF ((int)-1)
#endif

#ifndef FOPEN_MAX
#define FOPEN_MAX (8)
#endif

#ifndef FILENAME_MAX
#define FILENAME_MAX (256)
#endif

#ifndef L_tmpnam
#define L_tmpnam (64)
#endif

#ifndef SEEK_CUR
#define SEEK_CUR (0)
#endif

#ifndef SEEK_END
#define SEEK_END (1)
#endif

#ifndef SEEK_SET
#define SEEK_SET (2)
#endif

#ifndef TMP_MAX
#define TMP_MAX (8)
#endif

#ifndef stdin
#define stdin proc_table[proc_cur].streams[0]
#endif

#ifndef stdout
#define stdout proc_table[proc_cur].streams[1]
#endif

#ifndef stderr
#define stderr proc_table[proc_cur].streams[2]
#endif


/* FUNCTIONS */

/* Operations on Files */
int remove(const char *filename);
int rename(const char *old, const char *new);
FILE *tmpfile(void);
char *tmpnam(char *s);
/* File Access */
int fclose(FILE *stream);
int fflush(FILE *stream);
FILE *fopen(const char *filename, const char *mode);
FILE *freopen(const char *filename, const char *mode,
        FILE *stream);
void setbuf(FILE *stream, char *buf);
int setvbuf(FILE *stream, char *buf, int mode, size_t size);
/* Formatted I/O */
int fprintf(FILE *stream, const char *format, ...);
int fscanf(FILE *stream, const char *format, ...);
int printf(const char *format, ...);
int scanf(const char *format, ...);
int sprintf(char *s, const char *format, ...);
int sscanf(const char *s, const char *format, ...);
/* int vfprintf(FILE *stream, const char *format, va_list arg);
int vprintf(const char *format, va_list arg);
int vsprintf(char *s, const char *format, va_list arg); */
/* Character I/O */
int fgetc(FILE *stream);
char *fgets(char *s, int n, FILE *stream);
int fputc(int c, FILE *stream);
int fputs(const char *s, FILE *stream);
int getc(FILE *stream);
int getchar(void);
char *gets(char *s);
int putc(int c, FILE *stream);
int putchar(int c);
int puts(const char *s);
int ungetc(int c, FILE *stream);
/* Direct I/O */
size_t fread(void *ptr, size_t size, size_t nmemb,
        FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb,
        FILE *stream);
/* File Positioning */
int fgetpos(FILE *stream, fpos_t *pos);
int fseek(FILE *stream, long int offset, int whence);
int fsetpos(FILE *stream, const fpos_t *pos);
long int ftell(FILE *stream);
void rewind(FILE *stream);
/* Error Handling */
void clearerr(FILE *stream);
int feof(FILE *stream);
int ferror(FILE *stream);
void perror(const char *s);


#endif
