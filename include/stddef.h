#ifndef _INCLUDE_STDDEF_H
#define _INCLUDE_STDDEF_H

#ifndef _DEFINED_NULL
#define NULL 0
#define _DEFINED_NULL
#endif

#ifndef _DEFINED_PTRDIFF_T
typedef unsigned short int ptrdiff_t;
#define _DEFINED_PTRDIFF_T
#endif

#ifndef _DEFINED_SIZE_T
typedef unsigned short int size_t;
#define _DEFINED_SIZE_T
#endif

#ifndef _DEFINED_WCHAR_T
typedef unsigned short int wchar_t;
#define _DEFINED_WCHAR_T
#endif

#endif  // NDEF _INCLUDE_STDDEF_H
