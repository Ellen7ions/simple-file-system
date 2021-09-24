#include "cutils.h"
#include "gui.h"
#include <stdio.h>
#include <stdlib.h>

char *fs_cmds[] = {
    "mkdir",
    "rmdir",
    "cd",
    "ls",
    "pwd",
    "creat",
    "rm",
    "save",
    "reload",
    "menu",
    "quit"
};

int (*sys_cmds[])(int argc, char **argv) = {
    cmd_mkdir,
    cmd_rmdir,
    cmd_cd,
    cmd_ls,
    cmd_pwd,
    cmd_creat,
    cmd_rm,
    cmd_save,
    cmd_reload,
    cmd_menu,
    cmd_quit
};

int main() {
    gui_top(NULL);
    return 0;
}