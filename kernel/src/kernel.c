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

const char welcome[] =
"      ÍËÍ      É»  " "\n"
"   ÉÍÍÍÎÍÍÍ»   ××  " "\n"
"  É¼   ×   È»  ××  " "\n"
"  ×    ×    ×  ××  " "\n"
"  ×    ×    ×  ××  " "\n"
"  È»   ×   É¼  È¼  " "\n"
"   ÈÍÍÍÎÍÍÍ¼   É»  " "\n"
"      ÍÊÍ      È¼  " "\n"
"                   " "\n"
"   Welcome to è!   " "\n"
"      by 0xTJ      " "\n"
;

void kshell(fs_node_t *dev_dir) {
    int acia_fd = open("/dev/acia");
    char line_buf[64] = {0};
    size_t line_length = 0;
    
    if (acia_fd < 0)
        return;
    
    while (line_length < 64) {
        size_t did_read = read(acia_fd, line_buf + line_length, 1);
        if (did_read) {
            write(acia_fd, line_buf + line_length, 1);
            if (line_buf[line_length++] == '\n')
                break;
        }
    }
    
    if (line_buf[0] = 'l') {
        int i = 0;
        struct dirent *node = NULL;
        while ( (node = readdir_fs(proc_table[proc_cur].pwd, i)) != NULL) {
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

void init() {
    fs_node_t *dev_dir;

    fs_root = initialise_initrd((size_t)initrd_img);
    proc_post_setup(fs_root);
    
    dev_dir = finddir_fs(fs_root, "dev");
    dev_dir->flags |= FS_MOUNTPOINT;
    dev_dir->ptr = initialise_devfs();

    KLOG(INFO, "Adding devices");
    add_device(&acia_device, false, "acia");
    add_device(&ramdisk_device, true, "ramdisk");
    add_device(&null_device, false, "null");
    add_device(&zero_device, false, "zero");

    kshell(dev_dir);
    
    
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

    kprint(RIS);
    // {uint8_t i; for (i = 0; i < 0x400; i++) kput('\0');}
    // kprint("\n\n");
    // kprint(welcome);
    // kprint("\n\n");
    KLOG(INFO, "Starting PhiBang");
    proc_init_enter1(init);
    KLOG(INFO, "Halting");
}
