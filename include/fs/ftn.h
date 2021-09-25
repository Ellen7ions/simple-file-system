#ifndef _FTN_H_
#define _FTN_H_

#include "string.h"
#include "utils/utils.h"

typedef struct FileTreeNode {
    struct FileTreeNode *child;
    struct FileTreeNode *sibling;
    struct FileTreeNode *parent;

    char file_name[64];
    char file_type;
} FileTreeNode;

FileTreeNode *ftn_new(const char *file_name, char file_type, FileTreeNode *parent);

/**
 * free the memory of node.
 * @param cur
 */
void ftn_free_node(FileTreeNode *cur);


/**
 * add a new node to file tree.
 * @param cur
 * @param new_node
 */
void ftn_add_node(FileTreeNode *cur, FileTreeNode *new_node);

/**
 * remove a node from file tree.
 * @param cur
 */
void ftn_del_node(FileTreeNode *cur);

/**
 * show the file tree.
 * @param root
 */
void ftn_traverse(FileTreeNode *root);

/**
 * rename file node.
 * @param cur
 * @param name
 */
void ftn_rename(FileTreeNode *cur, const char *name);

#endif
