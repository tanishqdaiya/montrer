#include <stdio.h>

#include "config.h"

void
version_info(FILE *stream, const char *cmd_name)
{
    fprintf(stream,
            "%s (tanishqdaiya's %s) %s\n",
            cmd_name,
            PROGRAM_NAME,
            PROGRAM_VERSION);
    fprintf(stream, "This program was written by %s\n", PROGRAM_AUTHOR);
}
