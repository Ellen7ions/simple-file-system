#include "gui/gui.h"

void gui_show(GUI *gui) {

}

void gui_top(GUI *gui) {
    int *argc = (int *) malloc(sizeof(int));
    char **argv = (char **) malloc((sizeof(char *) * 10));
    while (1) {
        int cmd_index = gui_input_cmd(argc, argv);
        sys_cmds[cmd_index](argc, argv);
        if (strcmp(argv[0], "q") == 0 || strcmp(argv[0], "quit") == 0) {
            return;
        }
    }
}

int gui_input_cmd(int *argc, char **argv) {
    char cmd_buffer[128];
    char input_cmd[100];
    printf(">");
    fgets(cmd_buffer, 128, stdin);
    get_cmd(cmd_buffer, input_cmd);
    int cmd_index = get_cmd_index(input_cmd);
    str_to_arr(cmd_buffer, argc, argv);
    return cmd_index;
}
