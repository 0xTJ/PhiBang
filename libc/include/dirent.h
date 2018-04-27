#ifndef _INCLUDE_DIRENT_H
#define _INCLUDE_DIRENT_H

#include <stdint.h> // Actually just use normals instead of this

#ifndef _TYPEDEF_ino_t
#define _TYPEDEF_ino_t
typedef uint32_t ino_t;
#endif

struct dirent {
  ino_t d_ino;
  char d_name[64];
}; 

#endif
