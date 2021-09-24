#include "gui.h"

void gui_show(GUI *gui) {

}

void gui_top(GUI *gui) {
    while (1) {
        int *argc = (int *) malloc(sizeof(int));
        char **argv = (char **) malloc((sizeof(char *) * 10));
        gui_split_cmd(argc, argv);
        printf("cmd = %s\n", argv[0]);
        int i;
        printf("argv:\n");
        for (i = 0; i < *argc; i++) {
            printf("%s\n", argv[i]);
        }

        if (strcmp(argv[0], "q") == 0 || strcmp(argv[0], "quit") == 0) {
            return;
        }
    }
}

int gui_split_cmd(int *argc, char **argv) {
    char cmd_buffer[128];
    char input_cmd[100];
    printf(">");
    fgets(cmd_buffer, 128, stdin);
    get_cmd(cmd_buffer, input_cmd);
    int cmd_index = get_cmd_index(input_cmd);
    str_to_arr(cmd_buffer, argc, argv);
    return cmd_index;
}
