#ifndef _INCLUDE_STDLIB_H
#define _INCLUDE_STDLIB_H

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef _TYPEDEF_size_t
#define _TYPEDEF_size_t
typedef unsigned short size_t;
#endif

void          _Exit(int);
void          exit(int);
void          free(void *);
void         *malloc(size_t);

#endif
