#ifndef STR_H
#define STR_H

#include <stdbool.h>

/* Checks if the provided line contains only the given character c (unichar) */
bool is_unichar (char line[], char c);

/* Trims a whitespaces, tabs and newlines from the start and end of a string
   without allocating additional memory */
char *trim (char *str);

#endif //STR_H
