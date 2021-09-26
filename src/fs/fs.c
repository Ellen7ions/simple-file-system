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
    fs->total_file_cnt = 1;
}

FileTreeNode *fs_loc_node(const char *path) {
    if (strlen(path) == 0) return file_system->cur_node;
    int path_level;
    char *cpy_path = (char *) kmalloc(sizeof(char) * strlen(path));
    strcpy(cpy_path, path);
    char **paths = parse_path(cpy_path, &path_level);

    FileTreeNode *p;
    if (path[0] == '/') p = file_system->root;
    else p = file_system->cur_node;

    int i = 0;
    while (i < path_level && strcmp(p->file_name, paths[i]) != 0) {
        if (strcmp(paths[i], "..") == 0) {
            p = p->parent;
            i += 1;
            continue;
        } else if (strcmp(paths[i], ".") == 0) {
            i += 1;
            continue;
        } else {
            p = p->child;
        }
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
    file_system->total_file_cnt += 1;
    ftn_add_node(path_node, ftn_new(dir_name, 'D', NULL));
    return 0;
}

int fs_rmdir(const char *path, int force) {
    FileTreeNode *path_node = fs_loc_node(path);
    if (path_node == NULL) return -1;
    if (force || path_node->child == NULL) {
        ftn_del_node(path_node);
        file_system->total_file_cnt -= 1;
        return 0;
    }
    return 1;
}

int fs_cd(const char *path) {
    FileTreeNode *path_node = fs_loc_node(path);
    if (path_node == NULL || path_node->file_type == 'F') return -1;
    file_system->cur_node = path_node;
    return 0;
}

int fs_ls(const char *path) {
    FileTreeNode *path_node = path == NULL ? file_system->cur_node : fs_loc_node(path);
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

int fs_pwd() {
    FileTreeNode *path_node = file_system->cur_node;
    if (path_node == NULL) return -1;
    fs_print_pwd(path_node);
    printf("\n");
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
    file_system->total_file_cnt += 1;
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
    file_system->total_file_cnt -= 1;
    return 0;
}

void ft_to_arr(FileTreeNode *root, FileTreeNode *arr, int index) {
    if (root == NULL) return;
    arr[index] = *root;
    ft_to_arr(root->child, arr, 2 * index + 1);
    ft_to_arr(root->sibling, arr, 2 * index + 2);
}

void arr_to_ft(FileTreeNode **root, FileTreeNode *arr, int index, FileTreeNode *parent) {
    if (index >= file_system->total_file_cnt || root == NULL) return;
    *(root) = ftn_new(arr[index].file_name, arr[index].file_type, parent);
    arr_to_ft(&((*root)->child), arr, 2 * index + 1, *(root));
    arr_to_ft(&((*root)->sibling), arr, 2 * index + 2, *(root));
}

int fs_level(FileTreeNode *root) {
    if (root == NULL) return 0;
    int l = fs_level(root->child);
    int r = fs_level(root->sibling);
    return (l > r ? l : r) + 1;
}

int fs_save(const char *file_tree_path) {
    int max_level = fs_level(file_system->root);
    int max_node = (1 << max_level) - 1;
    FileTreeNode *ftn_arr = (FileTreeNode *) kmalloc(sizeof(FileTreeNode) * max_node);
    ft_to_arr(file_system->root, ftn_arr, 0);
    FILE *fp;
    fp = fopen(file_tree_path, "wb");
    if (fp == NULL) {
        printf("FILE ERROR!\n");
        exit(-1);
    }
    fwrite(ftn_arr, sizeof(FileTreeNode), max_node, fp);

    fclose(fp);
    return 0;
}

int fs_reload(const char *file_tree_path) {
    FILE *fp;
    fp = fopen(file_tree_path, "rb");
    if (fp == NULL) {
        printf("FILE ERROR!\n");
        exit(-1);
    }
    fseek(fp, 0, SEEK_END);
    file_system->total_file_cnt = ftell(fp) / sizeof(FileTreeNode);
    fseek(fp, 0, SEEK_SET);
    FileTreeNode *ftn_arr = (FileTreeNode *) kmalloc(sizeof(FileTreeNode) * file_system->total_file_cnt);
    fread(ftn_arr, sizeof(FileTreeNode), file_system->total_file_cnt, fp);
    arr_to_ft(&(file_system->root), ftn_arr, 0, file_system->root);
    file_system->cur_node = file_system->root;
    fclose(fp);
    return 0;
}
