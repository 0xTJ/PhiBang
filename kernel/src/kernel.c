#include <stdbool.h>
#include "proc.h"
#include "acia.h"
#include "ramdisk.h"
#include "devio.h"

void kprint(char *s) {
    while (*s != '\0')
        acia_put(*s++);
}

int mount(dev_t dev, char *path, int fs_num);

void test_mount(struct mount *mount) {
    mount->fs_root->ino = 1;
    mount->fs_root->fs_num = mount->fs_num;
    mount->fs_root->dev = mount->dev;
    mount->fs_root->ext_mount = 0;
}
void test_read_inode(struct inode *inodep) {
    return;
}
void test_write_inode(struct inode *inodep) {
    return;
}
ino_t test_find_ino(char *path) {
    if (path[0] == '/' && path[1] == '\0')
        return 1;
    else
        return 0;
}
size_t test_read(struct inode *inodep, uint8_t *buf, size_t size, off_t offset) {
    return 0;
}
ssize_t test_write(struct inode *inodep, uint8_t *buf, size_t size, off_t offset) {
    return -1;
}
int test_open(struct inode *inodep, ino_t ino) {
    return -1;
}

struct file_sys test_fs = {
    {
        test_mount,
        test_read_inode,
        test_write_inode,
        test_find_ino
    },
    {
        test_read,
        test_write,
        test_open
    }
};

void init() {
    kprint("\n\nLoading PhiBang\n\n");
    
    add_device(&acia_device, CHAR_DEV);
    add_device(&ramdisk_device, BLOCK_DEV);
    
    add_fs(&test_fs);
    
    mount(2, "/", 1);
    mount(2, "/a", 1);
    kprint("\n\nHalting\n\n");
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
