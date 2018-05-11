#include <stdbool.h>
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
"   ÉÍÍÍÎÍÍÍ»   ÇÇ  " "\n"
"  É¼   Ç   È»  ÇÇ  " "\n"
"  Ç    Ç    Ç  ÇÇ  " "\n"
"  Ç    Ç    Ç  ÇÇ  " "\n"
"  È»   Ç   É¼  È¼  " "\n"
"   ÈÍÍÍÎÍÍÍ¼   É»  " "\n"
"      ÍÊÍ      È¼  " "\n"
"                   " "\n"
"   Welcome to è!   " "\n"
"      by 0xTJ      " "\n"
;

void init() {
    fs_node_t *dev_dir;

    fs_root = initialise_initrd((size_t)initrd_img);
    proc_post_setup(fs_root);

    dev_dir = finddir_fs(fs_root, "dev");
    dev_dir->flags |= FS_MOUNTPOINT;
    dev_dir->ptr = initialise_devfs();

    KLOG(INFO, "Adding devices");
    add_device(&acia_device, false, "acia");
    // add_device(&ramdisk_device, true, "ramdisk");
    add_device(&null_device, false, "null");
    add_device(&zero_device, false, "zero");

    open("/dev/acia", O_RDONLY);
    open("/dev/acia", O_WRONLY|O_CREAT|O_APPEND);
    open("/dev/acia", O_WRONLY|O_CREAT|O_APPEND);
    
    // {
        // int i = 0;
        // struct dirent *node = NULL;
        // while ( (node = readdir_fs(proc_table[proc_cur].pwd, i)) != NULL) {
            // fs_node_t *fsnode = finddir_fs(proc_table[proc_cur].pwd, node->d_name);

            // kprint("Found file ");
            // kprint(node->d_name);

            // if ((fsnode->flags & (uint32_t)0x7) == FS_DIRECTORY) {
                // kprint("\n\t(directory)\n");
            // } else {
                // size_t j;
                // char buf[256];
                // size_t sz;

                // sz = read_fs(fsnode, 0, 256, buf);
                // kprint("\n\t contents: \"");
                // for (j = 0; j < sz; j++)
                    // kput(buf[j]);

                // kprint("\"\n");
            // }
            // i++;
        // }
    // }
    
    {
        fs_node_t *tmp = finddir_fs(proc_table[proc_cur].pwd, "sosh.bin");
        read_fs(tmp, 0, 0x0800, (void *)0xA000);
        KLOG(INFO, "Starting binary");
        ((void (*)())0xA000)();
        KLOG(INFO, "Done binary");
    }
}

extern struct block_meta heap;

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

    // kprint(RIS);
    // {size_t i; for (i = 0; i < 0x800; i++) kput('\0');}
    // kprint("\n\n");
    // kprint(welcome);
    kprint("\n\n");
    KLOG(INFO, "Starting PhiBang");

    proc_init_enter1(init);

    KLOG(INFO, "Halting");
}
