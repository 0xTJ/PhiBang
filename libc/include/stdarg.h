#ifndef _INCLUDE_STDARG_H
#define _INCLUDE_STDARG_H

typedef unsigned char * va_list;
#define va_start(marker, last)  { marker = (va_list)&last + sizeof(last); }
#define va_arg(marker, type)    *((type *)((marker += sizeof(type)) - sizeof(type)))
#define va_end(marker)          { marker = (va_list) 0; };
#define va_copy(dest, src)      { dest = src; }

#endif
