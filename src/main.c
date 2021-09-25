#include "gui/gui.h"
#include "fs/fs.h"
#include "fs/ftn.h"

int main() {
    file_system = (FileSystem *) kmalloc(sizeof(FileSystem));
    fs_init(file_system);

    FileTreeNode *root = file_system->root;
    ftn_add_node(root, ftn_new("home", 'D', root));
    ftn_add_node(root, ftn_new("etc", 'D', root));
    ftn_add_node(root, ftn_new("bin", 'D', root));
    ftn_add_node(root->child, ftn_new("desktop", 'D', root));
    ftn_traverse(root);
//    ftn_free_node(root);

    fs_loc_node("/home/desktop");
    int len = 0;
    char s[] = "/home/";
    parse_path(s, &len);
    return 0;
}