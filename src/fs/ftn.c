#include "fs/ftn.h"

void ftn_add_node(FileTreeNode *cur, FileTreeNode *new_node) {
    if (cur->child == NULL) {
        cur->child = new_node;
        new_node->parent = cur->child;
    } else {
        FileTreeNode *p = cur;
        while (p->sibling != NULL) p = p->sibling;
        p->sibling = new_node;
        new_node->parent = p;
    }
}

void ftn_free_node(FileTreeNode *cur) {
    if (cur == NULL) return;
    ftn_free_node(cur->child);
    ftn_free_node(cur->sibling);
    kfree(cur);
}

void ftn_del_node(FileTreeNode *cur) {
    cur->parent->child = cur->sibling;
    ftn_free_node(cur->child);
    kfree(cur);
}

void ftn_traverse(FileTreeNode *root) {
    if (root == NULL) return;
    printf("%s\n", root->file_name);
    ftn_traverse(root->child);
    ftn_traverse(root->sibling);
}

void ftn_rename(FileTreeNode *cur, const char *name) {
    strcpy(cur->file_name, name);
}