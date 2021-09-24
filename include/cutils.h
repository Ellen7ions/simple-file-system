#ifndef _CUTILS_H_
#define _CUTILS_H_

#include <stdlib.h>

int str_find(const char *s, char ch);

int str_find_start(const char *s, char ch, int s_pos);

void str_cpy_s(char *dst, int len, const char *src);

void str_to_arr(const char *buffer, int *len, char **result);

#endif