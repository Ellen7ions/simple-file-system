#ifndef _GUI_H_
#define _GUI_H_

#include <stdio.h>
#include <string.h>

#include "utils/utils.h"
#include "utils/cutils.h"
#include "cmd.h"

typedef struct GUI {
    int a;
} GUI;

void gui_top(GUI* gui);

int gui_input_cmd(int *argc, char **argv);

void gui_show(GUI* gui);

#endif