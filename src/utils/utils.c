#include "utils/utils.h"

char **parse_args(char *buffer, int *argc) {

}

char **parse_path(char *path, int *len) {
    char **result = (char **) kmalloc(sizeof(char *));
    char *pointer = strtok(path, "/");
    *len = 0;
    while (pointer != NULL) {
        *(result + *(len)) = pointer;
        *len += 1;
        pointer = strtok(NULL, "/");
    };
    return result;
}

void *kmalloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        printf("Error memory allocation !\n");
        exit(-1);
    }
    return ptr;
}

void kfree(void *ptr) {
    if (ptr == NULL) {
        printf("Error memory free !\n");
        exit(-1);
    }
    free(ptr);
}