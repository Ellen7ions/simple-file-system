#include "fs/fs.h"

void fs_init(FileSystem *fs) {
    fs->root = (FileTreeNode *) kmalloc(sizeof(FileTreeNode));
    fs->cur_node = fs->root;
    strcpy(fs->root->file_name, "/");
    fs->root->file_type = 'D';
    fs->root->child = NULL;
    fs->root->sibling = fs->root;
    fs->root->parent = fs->root;
}
