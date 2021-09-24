#ifndef _CMD_H_
#define _CMD_H_

#include <string.h>
#include "cutils.h"

extern char *fs_cmds[];

extern int (*sys_cmds[])(int argc, char **argv);

void get_cmd(const char *buffer, char *cmd);

int get_cmd_index(char* cmd);

// system cmds

int cmd_mkdir(int argc, char **argv);

int cmd_rmdir(int argc, char **argv);

int cmd_cd(int argc, char **argv);

int cmd_ls(int argc, char **argv);

int cmd_pwd(int argc, char **argv);

int cmd_creat(int argc, char **argv);

int cmd_rm(int argc, char **argv);

int cmd_save(int argc, char **argv);

int cmd_reload(int argc, char **argv);

int cmd_menu(int argc, char **argv);

int cmd_quit(int argc, char **argv);

#endif