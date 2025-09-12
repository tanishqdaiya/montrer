#ifndef _TDUTILS_H
#define _TDUTILS_H

#include <stdio.h>
#include <stdint.h>

/* Aborts the program with msg if cond is true. */
#define TRAP(cond, msg)                                                 \
    do {                                                                \
        if (cond) {                                                     \
            fprintf(stderr, "check failed: (%s)\n\t%s:%d: %s\n",	\
                    #cond, __FILE__, __LINE__, msg);                    \
            abort();                                                    \
        }								\
    } while (0)

/* Exit with an error message */
#define PANIC(...)                              \
    do {                                        \
        fprintf(stderr, __VA_ARGS__);           \
        fputc('\n', stderr);                    \
        exit(EXIT_FAILURE);                     \
    } while (0)

/* Compare variable with a string literal */
#define STRCMP_LIT(str, lit)                    \
    strcmp(str, "" lit "")

/* Returns 1 (true) if line consists only of character c.  Returns 0 (false)
   otherwise. */
uint8_t is_unichar(char line[], char c);

/* Trim leading and trailing whitespace in place. */
char *strtrim(char *str);

#endif /*_TDUTILS_H*/
