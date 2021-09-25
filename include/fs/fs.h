#ifndef _FS_H_
#define _FS_H_

#include "string.h"
#include "ftn.h"

typedef struct FileSystem {
    FileTreeNode *root;
    FileTreeNode *cur_node;
} FileSystem;

extern FileSystem *file_system;

/**
 * Init a file system.
 * @param fs
 */
void fs_init(FileSystem *fs);

// utils
FileTreeNode *fs_loc_node(const char *path);

void fs_print_pwd(FileTreeNode* cur);

// cmds
int fs_mkdir(const char *base_path, const char *dir_name);

int fs_rmdir(const char *path, int force);

int fs_cd(const char *path);

int fs_ls(const char *path);

int fs_pwd(const char *path);

int fs_creat(const char *path, const char *file_name);

int fs_rm(const char *path, const char *file_name);

#endif