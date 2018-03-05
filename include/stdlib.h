#ifndef _INCLUDE_STDLIB_H
#define _INCLUDE_STDLIB_H

#ifndef _DEFINED_NULL
#define NULL 0
#define _DEFINED_NULL
#endif

#ifndef _DEFINED_SIZE_T
typedef unsigned short int size_t;
#define _DEFINED_SIZE_T
#endif

void *malloc(size_t size);

#endif  // NDEF _INCLUDE_STDLIB_H
