#ifndef _INCLUDE_UNISTD_H
#define _INCLUDE_UNISTD_H

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef STDERR_FILENO
#define STDERR_FILENO (2)
#endif

#ifndef STDIN_FILENO
#define STDIN_FILENO (0)
#endif

#ifndef STDOUT_FILENO
#define STDOUT_FILENO (1)
#endif

#ifndef _TYPEDEF_size_t
#define _TYPEDEF_size_t
typedef unsigned short size_t;
#endif

#ifndef _TYPEDEF_ssize_t
#define _TYPEDEF_ssize_t
typedef unsigned short ssize_t;
#endif

#ifndef _TYPEDEF_pid_t
#define _TYPEDEF_pid_t
typedef unsigned short pid_t;
#endif

int          chdir(const char *);
int          close(int);
pid_t        fork(void);
pid_t        getpid(void);
pid_t        getppid(void);
size_t       read(int, void *, size_t);
ssize_t      write(int, const void *, size_t);

#endif
