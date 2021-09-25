#include "fs/fs.h"

FileSystem *file_system;

void fs_init(FileSystem *fs) {
    fs->root = (FileTreeNode *) kmalloc(sizeof(FileTreeNode));
    fs->cur_node = fs->root;
    strcpy(fs->root->file_name, "/");
    fs->root->file_type = 'D';
    fs->root->child = NULL;
    fs->root->sibling = NULL;
    fs->root->parent = fs->root;
}

FileTreeNode *fs_loc_node(const char *path) {
    if (strlen(path) == 0) return NULL;
    int path_level;
    char *cpy_path = (char *) kmalloc(sizeof(char) * strlen(path));
    strcpy(cpy_path, path);
    char **paths = parse_path(cpy_path, &path_level);

    FileTreeNode *p;
    if (path[0] == '/') p = file_system->root;
    else p = file_system->cur_node;

    int i = 0;
    while (i < path_level && strcmp(p->file_name, paths[i]) != 0) {
        p = p->child;
        if (p == NULL) goto finish;
        while (strcmp(p->file_name, paths[i]) != 0) {
            p = p->sibling;
            if (p == NULL) goto finish;
        }
        i += 1;
    }
    finish:
    return p;
}

void fs_print_pwd(FileTreeNode *cur) {
    if (cur->parent == cur) {
        return;
    }
    fs_print_pwd(cur->parent);
    printf("/%s", cur->file_name);
}

int fs_mkdir(const char *base_path, const char *dir_name) {
    FileTreeNode *path_node = fs_loc_node(base_path);
    if (path_node == NULL) return -1;
    FileTreeNode *p = path_node->child;
    while (p != NULL) {
        if (strcmp(p->file_name, dir_name) == 0) return 1;
        p = p->sibling;
    }
    ftn_add_node(path_node, ftn_new(dir_name, 'D', NULL));
    return 0;
}

int fs_rmdir(const char *path, int force) {
    FileTreeNode *path_node = fs_loc_node(path);
    if (path_node == NULL) return -1;
    if (force || path_node->child == NULL) {
        ftn_del_node(path_node);
        return 0;
    }
    return 1;
}

int fs_cd(const char *path) {
    FileTreeNode *path_node = fs_loc_node(path);
    if (path_node == NULL) return -1;
    file_system->cur_node = path_node;
    return 0;
}

int fs_ls(const char *path) {
    FileTreeNode *path_node = fs_loc_node(path);
    if (path_node == NULL) return -1;
    path_node = path_node->child;
    int cnt = 0;
    while (path_node != NULL) {
        printf("[%c] %s\n", path_node->file_type, path_node->file_name);
        path_node = path_node->sibling;
        cnt += 1;
    }
    printf("total %d files.\n", cnt);
    return 0;
}

int fs_pwd(const char *path) {
    FileTreeNode *path_node = fs_loc_node(path);
    if (path_node == NULL) return -1;
    fs_print_pwd(path_node);
    return 0;
}

int fs_creat(const char *path, const char *file_name) {
    FileTreeNode *path_node = fs_loc_node(path);
    if (path_node == NULL) return -1;
    FileTreeNode *p = path_node->child;
    while (p != NULL) {
        if (strcmp(p->file_name, file_name) == 0) return 1;
        p = p->sibling;
    }
    ftn_add_node(path_node, ftn_new(file_name, 'F', NULL));
    return 0;
}

int fs_rm(const char *path, const char *file_name) {
    FileTreeNode *path_node = fs_loc_node(path);
    if (path_node == NULL) return -1;
    FileTreeNode *p = path_node->child;
    while (p != NULL) {
        if (strcmp(p->file_name, file_name) == 0) goto found;
        p = p->sibling;
    }
    return 1;
    found:
    ftn_del_node(p);
    return 0;
}