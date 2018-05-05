#include <stdio.h>
#include <fcntl.h>

FILE _io_files[FOPEN_MAX] = {
    {
        .fd = 0,
        .oflag = O_RDONLY,
        .is_eof = 0,
        .is_err = 0
    },
    {
        .fd = 1,
        .oflag = O_WRONLY|O_CREAT|O_APPEND,
        .is_eof = 0,
        .is_err = 0
    },
    {
        .fd = 2,
        .oflag = O_WRONLY|O_CREAT|O_APPEND,
        .is_eof = 0,
        .is_err = 0
    },
};
