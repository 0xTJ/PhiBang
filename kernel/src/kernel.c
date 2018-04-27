#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include "proc.h"
#include "dev.h"
#include "dev/acia.h"
#include "dev/null.h"
#include "dev/ramdisk.h"
#include "dev/zero.h"
#include "fs.h"
#include "fs/devfs.h"
#include "fs/initrd.h"
#include "kio.h"
#include "../../initrd/initrd.img.h"

void init() {
    fs_node_t *dev_dir;
    kprint("\n\nLoading PhiBang\n\n");

    fs_root = initialise_initrd((size_t)initrd_img);
    dev_dir = finddir_fs(fs_root, "dev");
    dev_dir->flags |= FS_MOUNTPOINT;
    dev_dir->ptr = initialise_devfs();

    add_device(&acia_device, false, "acia");
    add_device(&ramdisk_device, true, "ramdisk");
    add_device(&null_device, false, "null");
    add_device(&zero_device, false, "zero");

    {
        int i = 0;
        struct dirent *node = NULL;
        while ( (node = readdir_fs(dev_dir->ptr, i)) != NULL) {
            fs_node_t *fsnode = finddir_fs(dev_dir->ptr, node->d_name);

            kprint("Found file ");
            kprint(node->d_name);

            if ((fsnode->flags & (uint32_t)0x7) == FS_DIRECTORY) {
                kprint("\n\t(directory)\n");
            } else {
                size_t j;
                char buf[1];
                size_t sz;
                
                sz = read_fs(fsnode, 0, 1, buf);
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
