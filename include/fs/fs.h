#ifndef _FS_H_
#define _FS_H_

#include "string.h"
#include "ftn.h"

typedef struct FileSystem {
    FileTreeNode *root;
    FileTreeNode *cur_node;
} FileSystem;

/**
 * Init a file system.
 * @param fs
 */
void fs_init(FileSystem *fs);

#endif