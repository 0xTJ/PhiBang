#include <stdio.h>

FILE _io_files[FOPEN_MAX];

void _setup_stdio() {
    _io_files[0].fd = 0;
    _io_files[0].mode = _MODE_READ;
    _io_files[0].is_eof = 0;
    _io_files[0].is_err = 0;
    
    _io_files[1].fd = 1;
    _io_files[1].mode = _MODE_WRITE;
    _io_files[1].is_eof = 0;
    _io_files[1].is_err = 0;
    
    _io_files[2].fd = 2;
    _io_files[2].mode = _MODE_WRITE;
    _io_files[2].is_eof = 0;
    _io_files[2].is_err = 0;
}
