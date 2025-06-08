#include <stdbool.h>
#include <string.h>
#include "str.h"

bool
is_unichar (char line[], char c)
{
  int i = 0;
  while (line[i] != '\n' && line[i] != '\0')
    if (line[i++] != c)
      return false;

  if (i < 1)
    return false;

  return true;
}

char *
trim (char *str)
{
  while (*str == ' ' || *str == '\t' || *str == '\n')
    ++str;

  if (*str == '\0')
    return str;

  char *end = (str + strlen (str)) - 1;
  while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
    --end;

  *(end + 1) = '\0';

  return str;
}
