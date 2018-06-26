#include <stdbool.h>
#include <fcntl.h>
#include <eof.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "proc.h"
#include "delrel.h"
#include "dev.h"
#include "dev/acia.h"
#include "dev/null.h"
#include "dev/ramdisk.h"
#include "dev/zero.h"
#include "fs.h"
#include "fs/devfs.h"
#include "fs/initrd.h"
#include "kio.h"
#include "sched.h"
#include "../../initrd/initrd.img.h"

const char welcome[] =
"      ÕÀÕ      …ª  " "\n"
"   …ÕÕÕŒÕÕÕª   ««  " "\n"
"  …º   «   »ª  ««  " "\n"
"  «    «    «  ««  " "\n"
"  «    «    «  ««  " "\n"
"  »ª   «   …º  »º  " "\n"
"   »ÕÕÕŒÕÕÕº   …ª  " "\n"
"      Õ Õ      »º  " "\n"
"                   " "\n"
"   Welcome to Ë!   " "\n"
"      by 0xTJ      " "\n"
;

void readOfSize(size_t size, void *position) {
    size_t i = 0;
    while (i < size) {
        int get = acia_device.get();
        if (get == EOF)
            continue;
        *((uint8_t *) ((uint8_t *) position + i)) = get;
        acia_device.put('.');
        ++i;
    }
}

extern void *sysc_ret;
extern void *curr_sp;
void loadBin() {
    size_t size = 0x0000;
    struct drlHeader header;
    struct drlEntry *entries;

    kprint("Enter HEX size of binary file 0x");
    while (true) {
        int get = acia_device.get();
        if (get == EOF) {
            continue;
        } else if (get == '\n') {
            acia_device.put(get);
            break;
        } else if ('0' <= get && get <= '9') {
            acia_device.put(get);
            size = size * 0x10 + (get - '0');
        } else if ('A' <= get && get <= 'F') {
            acia_device.put(get);
            size = size * 0x10 + (get - 'A' + 0xA);
        } else if ('a' <= get && get <= 'f') {
            acia_device.put(get);
            size = size * 0x10 + (get - 'a' + 0xA);
        } else {
            continue;
        }
    }

    kprint("Length is ");
    kput_uint16(size);
    kprint("\n");

    kprint("Reading ");
    kput_uint16(sizeof(struct drlHeader));
    kprint("bytes\n");
    readOfSize(sizeof(struct drlHeader), &header);

    entries = kmalloc(sizeof(struct drlEntry) * header.offLen);
    kprint("Reading ");
    kput_uint16(sizeof(struct drlEntry) * header.offLen);
    kprint("bytes\n");
    readOfSize(sizeof(struct drlEntry) * header.offLen, (void *)entries);

    kprint("Reading ");
    kput_uint16(size - (sizeof(struct drlHeader) + sizeof(struct drlEntry) * header.offLen));
    kprint("bytes\n");
    readOfSize(size - (sizeof(struct drlHeader) + sizeof(struct drlEntry) * header.offLen), (void *)0xA000);
    
    processDrl(&header, entries, (void *)0xA000, (void *)0xA800);
    sysc_ret = (void *)0xA000;
    curr_sp = (void *)0xB000;
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
    // add_device(&ramdisk_device, true, "ramdisk");
    add_device(&null_device, false, "null");
    add_device(&zero_device, false, "zero");

    open("/dev/acia", O_RDONLY);
    open("/dev/acia", O_WRONLY|O_CREAT|O_APPEND);
    open("/dev/acia", O_WRONLY|O_CREAT|O_APPEND);

    __asm
    call (enter_kernel)
    __endasm;
    loadBin();
    KLOG(INFO, "About to exit kernel");
    __asm
    call (exit_kernel);
    __endasm;
    KLOG(INFO, "Exited kernel");
    __asm
    ld      hl, #0xA000
    jp      (hl)
    __endasm;

    __asm
    call (enter_kernel)
    __endasm;
    KLOG(INFO, "Dropping down to Sosh");
    execvp("/sosh.bin", NULL);
    __asm
    call (exit_kernel);
    __endasm;
    KLOG(ERROR, "Failed Sosh");
    while (true) {}
    // Never try to return here. The previous stack has been obliterated, and you'll return on an unknown value.
}

extern struct block_meta heap;
extern void *sysc_ret;
extern void *curr_sp;
void bootstrap_exec(void);

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
    proc_cur = 1;
    sysc_ret = init;
    curr_sp = proc_table[1].stack_pointer;
    bootstrap_exec();
}
