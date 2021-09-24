#include "gui/cmd.h"

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

int (*sys_cmds[])(const int *argc, char **argv) = {
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

int cmd_mkdir(const int *argc, char **argv) {
    if (argc == 0) return -1;
    char *dir_path = argv[0];
    
}

int cmd_rmdir(const int *argc, char **argv) {
    if (argc == 0) return -1;
    char *dir_path = argv[0];
    
}

int cmd_cd(const int *argc, char **argv) {
    if (argc == 0) return -1;
    char *dir_path = argv[0];
    
}

int cmd_ls(const int *argc, char **argv) {
    if (argc == 0) return -1;
    char *dir_path = argv[0];
    
}

int cmd_pwd(const int *argc, char **argv) {
    if (argc == 0) return -1;
    char *dir_path = argv[0];
    
}

int cmd_creat(const int *argc, char **argv) {
    if (argc == 0) return -1;
    char *dir_path = argv[0];
    
}

int cmd_rm(const int *argc, char **argv) {
    if (argc == 0) return -1;
    char *dir_path = argv[0];

}

int cmd_save(const int *argc, char **argv) {
    if (argc == 0) return -1;
    char *dir_path = argv[0];
    
}

int cmd_reload(const int *argc, char **argv) {
    if (argc == 0) return -1;
    char *dir_path = argv[0];
    
}

int cmd_menu(const int *argc, char **argv) {
    if (argc == 0) return -1;
    char *dir_path = argv[0];
    
}

int cmd_quit(const int *argc, char **argv) {
    if (argc == 0) return -1;
    char *dir_path = argv[0];
    
}

void get_cmd(const char *buffer, char *cmd) {
    int f_space_index = str_find(buffer, ' ');
    f_space_index = (f_space_index == -1) ? strlen(buffer) - 1 : f_space_index;
    str_cpy_s(cmd, f_space_index, buffer);
}

int get_cmd_index(char* cmd) {
    int i;
    int cmds_len = 11;
    for (i = 0; i < cmds_len; i++) {
        if (strcmp(fs_cmds[i], cmd) == 0) {
            return i;
        }
    }
    return -1;
}
