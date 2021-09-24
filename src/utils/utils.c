#include "utils/utils.h"

char **parse_args(char *buffer, int *argc) {
    
}

void *kmalloc(size_t size) {
    void* ptr = malloc(size);
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