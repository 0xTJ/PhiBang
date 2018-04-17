#ifndef _INCLUDE_TYPES_H
#define _INCLUDE_TYPES_H

#include <stdint.h> // Actually just use normals instad of this

#ifndef _TYPEDEF_dev_t
#define _TYPEDEF_dev_t
typedef uint8_t dev_t;
#endif

#ifndef _TYPEDEF_ino_t
#define _TYPEDEF_ino_t
typedef uint32_t ino_t;
#endif

#ifndef _TYPEDEF_off_t
#define _TYPEDEF_off_t
typedef uint32_t off_t;
#endif

#ifndef _TYPEDEF_size_t
#define _TYPEDEF_size_t
typedef uint16_t size_t;
#endif

#ifndef _TYPEDEF_ssize_t
#define _TYPEDEF_ssize_t
typedef int32_t ssize_t;
#endif

#endif
