#include "filesys.h"
#include <stddef.h>
#include <string.h>
#include "mem.h"
#include "devio.h"

#define INODE_COUNT 32
struct inode ino_tab[INODE_COUNT] = {
    {
        1,
        0,
        0,
        0,
        0
    }
};
const struct inode *root_node = ino_tab;

#define FS_COUNT 4
struct file_sys *fs_tab[FS_COUNT] = { NULL };

#define MOUNT_COUNT 8
struct mount mnt_tab[MOUNT_COUNT];

unsigned short add_fs(struct file_sys *fs) {
    unsigned short i = 1;
    unsigned short found_spot = 0;

    do {
        if (fs_tab[i] == NULL) {
            found_spot = i;
            break;
        }
    } while (i++ < DEVICE_COUNT - 1);

    if (found_spot > 0)
        fs_tab[found_spot] = fs;

    return found_spot;
}

struct inode *alloc_inode() {
    unsigned short i;
    for (i = 1; i < INODE_COUNT; i++) {
        if (ino_tab[i].ino == 0)
            return ino_tab + i;
    }

    return NULL;
}

void free_inode(struct inode *inode) {
    memset(inode, 0, sizeof(struct inode));
}

unsigned short alloc_mount() {
    unsigned short i;
    for (i = 1; i < MOUNT_COUNT; i++) {
        if (mnt_tab[i].mount_point == NULL) {
            memset(mnt_tab + i, 0, sizeof(struct mount));
            mnt_tab[i].mount_point = NULL; // Just in case NULL != 0
            return i;
        }
    }

    return 0;
}

void free_mount(unsigned short mount_num) {
    memset(mnt_tab + mount_num, 0, sizeof(struct mount));
    mnt_tab[mount_num].mount_point = NULL; // Just in case NULL != 0
}

void kprint(char *s);
extern struct block_meta heap;
struct inode *follow_path(struct inode *root, char *path) {
    size_t done_path = 1;
    struct inode *working;
    char *path_base = path;
    char *part_path;
    char *part_path_base;

    {
        char tmp[2] = { -1, '\0' };
        kprint("Starting search at inode ");
        tmp[0] = '0' + root->ino;
        kprint(tmp);
        kprint(" of device ");
        tmp[0] = '0' + root->dev;
        kprint(tmp);
        kprint(" following path \"");
        kprint(path);
        kprint("\".\n");
    }

    if (root->mnt_num == 0 && root->dev == 0 && root->ext_mount == 0) {
        working = root;
        goto end;
    }
        
    working = alloc_inode();
    part_path = kalloc(strlen(path) + 1, &heap);
    part_path_base = part_path;

    if (part_path == NULL)
        return NULL;
    part_path[0] = '/';
    part_path[1] = '\0';

    memcpy(working, root, sizeof(struct inode));


    while (path[done_path] != '\0') {
        {
            char tmp[2] = { 0 };
            kprint("\"");
            kprint(path);
            kprint("\":\"");
            kprint(part_path);
            kprint("\":\"");
            kprint(path + done_path);
            kprint("\"\n");
        }

        if (working->ext_mount != 0) {
            {
                char tmp[2] = { 0 };
                kprint("Switching from \"");
                kprint(part_path);
                kprint("\" on mount ");
                tmp[0] = '0' + working->mnt_num;
                kprint(tmp);
            }
            working = (mnt_tab + working->ext_mount)->fs_root;
            part_path[0] = '/';
            part_path[1] = '\0';
            path = path_base + done_path - 1;
            {
                char tmp[2] = { 0 };
                kprint(" to \"");
                kprint(part_path);
                kprint("\" on mount ");
                tmp[0] = '0' + working->mnt_num;
                kprint(tmp);
                kprint(". Following path \"");
                kprint(path);
                kprint("\".\n");
            }
        } else { // On same mount
            ino_t ino;
            done_path += get_path_unit(part_path, path);

            ino = fs_tab[working->mnt_num]->fs_ops.find_ino(part_path);

            {
                char tmp[2] = { 0 };
                kprint("Path \"");
                kprint(part_path);
                kprint("\" on mount ");
                tmp[0] = '0' + working->mnt_num;
                kprint(tmp);
                kprint(" is inode ");
                tmp[0] = '0' + ino;
                kprint(tmp);
                kprint(".\n");
            }

            if (ino > 0) {
                working->ino = ino;
                fs_tab[working->mnt_num]->fs_ops.read_inode(working);
            } else {
                // TODO: Cleanup what was opened, if anything

                {
                    char tmp[2] = { 0 };
                    kprint("Failed search for \"");
                    kprint(part_path);
                    kprint("\" on mount ");
                    tmp[0] = '0' + working->mnt_num;
                    kprint(tmp);
                    kprint(".\n");
                }

                kfree(part_path_base);
                free_inode(working);

                return NULL;
            }
        }
    }

end:
    {
        char tmp[2] = { -1, '\0' };
        kprint("Finished search for \"");
        kprint(path_base);
        kprint("\" at inode ");
        tmp[0] = '0' + working->ino;
        kprint(tmp);
        kprint(" of mount ");
        tmp[0] = '0' + working->mnt_num;
        kprint(tmp);
        kprint(".\n");
    }

    kfree(part_path_base);
    return working;
}

size_t get_path_unit(char *part_path, char *path) {
    size_t part_len = strlen(part_path);
    char *part_path_base = part_path;
    part_path += part_len;
    path += part_len;

    if (*path == '\0')
        return 0;
    
    if (*path == '/') {
        *(part_path++) = *(path++);
        return 1;
    }
    
    while (*path != '\0' && *path != '/') {
        *(part_path++) = *(path++);
    }

    *part_path = '\0';

    return strlen(part_path_base) - part_len;
}
