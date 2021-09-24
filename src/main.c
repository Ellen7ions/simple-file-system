#include "gui/gui.h"
#include "fs/fs.h"
#include "fs/ftn.h"

int main() {
    FileTreeNode *root = (FileTreeNode *) kmalloc(sizeof(FileTreeNode));
    FileTreeNode *new_node = (FileTreeNode *) kmalloc(sizeof(FileTreeNode));
    strcpy(new_node->file_name, "home");
    strcpy(root->file_name, "/");
    new_node->file_type = 'D';
    root->file_type = 'F';
    ftn_add_node(root, new_node);
    ftn_traverse(root);
    return 0;
}