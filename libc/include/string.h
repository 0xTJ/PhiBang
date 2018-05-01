#ifndef _INCLUDE_STRING_H
#define _INCLUDE_STRING_H

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef _TYPEDEF_size_t
typedef unsigned short size_t;
#define _TYPEDEF_size_t
#endif

void    *memcpy(void *, const void *, size_t);
void    *memmove(void *, const void *, size_t);
void    *memset(void *, int, size_t);
int      strcmp(const char *, const char *);
char    *strcpy(char *restrict, const char *restrict);
size_t   strlen(const char *);

#endif
