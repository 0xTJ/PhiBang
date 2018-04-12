#ifndef _INCLUDE_SYS_RESOURCE_H
#define _INCLUDE_SYS_RESOURCE_H

#ifndef _TYPEDEF_rlim_t
typedef unsigned long rlim_t;
#endif

#ifndef RLIM_INFINITY
#define RLIM_INFINITY (-1)
#endif

#ifndef RLIM_SAVED_MAX
#define RLIM_SAVED_MAX RLIM_INFINITY
#endif

#ifndef RLIM_SAVED_CUR
#define RLIM_SAVED_CUR RLIM_INFINITY
#endif

#ifndef RLIMIT_NOFILE
#define RLIMIT_NOFILE (8)
#endif

#ifndef RLIMIT_STACK
#define RLIMIT_STACK (1024)
#endif

#ifndef RLIMIT_AS
#define RLIMIT_AS (4096)
#endif

#endif
