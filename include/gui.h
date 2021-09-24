#ifndef _GUI_H_
#define _GUI_H_

#include <stdio.h>
#include <string.h>
#include "cutils.h"
#include "cmd.h"

typedef struct GUI {
    int a;
} GUI;

void gui_top(GUI* gui);

int gui_split_cmd(int *argc, char **argv);

void gui_show(GUI* gui);

#endif