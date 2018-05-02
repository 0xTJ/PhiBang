    .module heap
    HEAP_SIZE = 0x1000

	.area   _HEAP
_heap::
    .blkb   HEAP_SIZE
