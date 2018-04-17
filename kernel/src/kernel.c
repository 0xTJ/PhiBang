#include <stdbool.h>
#include "proc.h"
#include "acia.h"
#include "fs.h"
#include "initrd.h"
#include "../../initrd/initrd.img.h"

void kprint(char *s) {
    while (*s != '\0')
        acia_put(*s++);
}

void kput(char c) {
    acia_put(c);
}

const char hex[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

void kprintaddr(void *val) {
    kput(hex[((uint16_t)val >> 12) & 0xF]);
    kput(hex[((uint16_t)val >> 8) & 0xF]);
    kput(hex[((uint16_t)val >> 4) & 0xF]);
    kput(hex[((uint16_t)val >> 0) & 0xF]);
}

void init() {
    kprint("\n\nLoading PhiBang\n\n");
    
    fs_root = initialise_initrd((size_t)initrd_img);
    
    {
        int i = 0;
        struct dirent *node = NULL;
        while ( (node = readdir_fs(fs_root, i)) != 0) {
            fs_node_t *fsnode = finddir_fs(fs_root, node->d_name);
            
            kprint("Found file ");
            kprint(node->d_name);
            
            if ((fsnode->flags & (uint32_t)0x7) == FS_DIRECTORY) {
                kprint("\n\t(directory)\n");
            } else {
                size_t j;
                char buf[256];
                size_t sz = read_fs(fsnode, 0, 256, buf);
                kprint("\n\t contents: \"");
                for (j = 0; j < sz; j++)
                    kput(buf[j]);

                kprint("\"\n");
            }
            i++;
        } 
    }
}

struct block_meta heap;

void main() {
    __asm
    push    hl
    ld      hl, #l__HEAP
    ld      (_heap), hl ;// Only works if size is the first element of struct block_meta
    pop hl
    __endasm;

    heap.size = heap.size - sizeof(struct block_meta);
    heap.next = NULL;
    heap.free = true;

    proc_init_enter1(init);
}
