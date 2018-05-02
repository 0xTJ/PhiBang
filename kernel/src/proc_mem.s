    .module proc_mem
    
    .area   _PROCMEM (ABS)
    .org    0xA000
_proc_mem::
    .blkb   0x1000
