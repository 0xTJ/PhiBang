#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
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

    KLOG(INFO, "About to enter kernel");

    __asm
    call (enter_kernel)
    __endasm;
    KLOG(INFO, "Entered kernel");
    KLOG(INFO, "Loading binary");
    execvp("/sosh.bin", NULL);
    KLOG(INFO, "Loaded binary");
    KLOG(INFO, "About to exit kernel");
    __asm
    call (exit_kernel);
    __endasm;
    KLOG(INFO, "Exited kernel");
    KLOG(INFO, "About to jump into user");
    __asm
    ld      hl, #0xA000
    jp      (hl)
    __endasm;
    KLOG(INFO, "Failed binary");
    // Never try to return here. The previous stack has been obliterated, and you'll return on an unknown value.
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
