#ifndef _INCLUDE_STDDEF_H
#define _INCLUDE_STDDEF_H


/* TYPES */

#ifndef _TYPEDEF_PTRDIFF_T
typedef unsigned short int ptrdiff_t;
#define _TYPEDEF_PTRDIFF_T
#endif

#ifndef _TYPEDEF_SIZE_T
typedef unsigned short int size_t;
#define _TYPEDEF_SIZE_T
#endif

#ifndef _TYPEDEF_WCHAR_T
typedef unsigned short int wchar_t;
#define _TYPEDEF_WCHAR_T
#endif


/* MACROS */

#ifndef NULL
#define NULL (0)
#endif

#ifndef offsetof
#define offsetof( type, member_designator ) (0)
#endif


#endif
