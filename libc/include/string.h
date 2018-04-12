#ifndef _INCLUDE_STRING_H
#define _INCLUDE_STRING_H

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef _TYPEDEF_size_t
typedef unsigned short size_t;
#define _TYPEDEF_size_t
#endif

void *memcpy(void *s1, const void *s2, size_t n);
void *memmove(void *s1, const void *s2, size_t n);
void *memset(void *s, int c, size_t n);
size_t strlen(const char *s);

#endif
