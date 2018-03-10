#ifndef _INCLUDE_STDIO_H
#define _INCLUDE_STDIO_H

/* TYPES */

#ifndef _TYPEDEF_size_t
typedef unsigned short int size_t;
#define _TYPEDEF_size_t
#endif

#ifndef _TYPEDEF_fpos_t
typedef unsigned int fpos_t;
#define _TYPEDEF_fpos_t
#endif

struct vnode;

#ifndef _TYPEDEF_FILE
typedef struct {
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
#define _IOFBF (1)
#define _IOLBF (2)
#define _IONBF (3)
#define BUFSIZ (256)
#define EOF ((int)-1)
#define FOPEN_MAX (8)
#define FILENAME_MAX (256)
#define L_tmpnam (64)
#define SEEK_CUR (0)
#define SEEK_END (1)
#define SEEK_SET (2)
#define TMP_MAX (8)
                          
/*                          
#define	stdin	(&_iob[0])
#define	stdout	(&_iob[1])
#define	stderr	(&_iob[2])
*/

#define	getchar()   getc(stdin)
#define	putchar(x)  putc(x,stdout)
#define	feof(p)     ((p)->eof_ind)
#define	ferror(p)   ((p)->err_ind)

#endif
