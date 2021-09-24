#ifndef _CMD_H_
#define _CMD_H_

#include <string.h>
#include "utils/cutils.h"

extern char *fs_cmds[];

extern int (*sys_cmds[])(const int *argc, char **argv);

void get_cmd(const char *buffer, char *cmd);

int get_cmd_index(char* cmd);

// system cmds

int cmd_mkdir(const int *argc, char **argv);

int cmd_rmdir(const int *argc, char **argv);

int cmd_cd(const int *argc, char **argv);

int cmd_ls(const int *argc, char **argv);

int cmd_pwd(const int *argc, char **argv);

int cmd_creat(const int *argc, char **argv);

int cmd_rm(const int *argc, char **argv);

int cmd_save(const int *argc, char **argv);

int cmd_reload(const int *argc, char **argv);

int cmd_menu(const int *argc, char **argv);

int cmd_quit(const int *argc, char **argv);

#endif