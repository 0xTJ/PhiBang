#ifndef _INCLUDE_FCNTL_H
#define _INCLUDE_FCNTL_H

#define O_CREAT (1 << 3)
#define O_TRUNC (1 << 4)
#define O_APPEND (1 << 5)
#define O_ACCMODE (0b111)
#define O_EXEC (0b001)
#define O_RDONLY (0b010)
#define O_RDWR (0b011)
#define O_SEARCH (0b101)
#define O_WRONLY (0b100)

int open(const char *, int/*, ...*/);

#endif
