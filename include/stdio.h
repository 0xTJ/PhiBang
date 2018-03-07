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



#endif
