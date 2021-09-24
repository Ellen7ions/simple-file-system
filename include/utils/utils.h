#ifndef _UTILS_H_
#define _UTILS_H_

#include "stdio.h"
#include "stdlib.h"

char **parse_args(char *buffer, int *argc);

void *kmalloc(size_t size);

void kfree(void *ptr);

#endif