#ifndef _INCLUDE_UNISTD_H
#define _INCLUDE_UNISTD_H

#ifndef _TYPEDEF_size_t
typedef unsigned short size_t;
#endif

#ifndef _TYPEDEF_ssize_t
typedef unsigned short ssize_t;
#endif

#ifndef _TYPEDEF_pid_t 
typedef unsigned short pid_t;
#endif

int          chdir(const char *);
int          close(int);
pid_t        fork(void);
pid_t        getpid(void);
pid_t        getppid(void);
ssize_t      read(int, void *, size_t);
ssize_t      write(int, const void *, size_t);

#endif
