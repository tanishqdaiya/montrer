#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tdutils.h"

uint8_t
is_unichar(char line[], char c)
{
    int i = 0;
    while (line[i] != '\n' && line[i] != '\0')
        if (line[i++] != c)
            return 0;

    if (i < 1)
        return 0;

    return 1;
}

char *
strslice(char *str, uint32_t start, uint32_t end)
{
    size_t sz, n;
    char *new_str;

    n = end - start;
    sz = sizeof(char) * (n + 1);
    new_str = (char*)malloc(sizeof(char) * (n + 1));
    if (new_str == NULL)
        PANIC("malloc(%zu): Error allocating memory!", sz);

    size_t i;
    for (i = 0; i < n; ++i)
        new_str[i] = str[start + i];
    new_str[i] = '\0';

    return new_str;
}

char *
strtrim(char *str)
{
    char *pstr;
    size_t a, b;

    a = 0;
    b = strlen(str);

    pstr = str;
    while (isspace(*pstr)) {
        pstr++;
        a++;
    }

    pstr = str + b - 1;
    while (isspace(*pstr)) {
        pstr--;
        b--;
    }

    return strslice(str, a, b);
}
