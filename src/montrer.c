/* montrer.c -- Transforms structured mardown into something better: a full set
   of clean and minimal HTML slides that you can use to present your ideas.
   Author: Tanishq Daiya <tanishqdaiya@yahoo.com>

   This file is a part of montrer (https://github.com/tanishqdaiya/montrer)

   montrer is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   See <https://www.gnu.org/licenses/> for details. */

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "tdutils.h"
#include "montrer.h"

struct montrer_args
{
    uint8_t help;
    uint8_t version;
    const char *in_filepath;
};

static void
usage(const char *progname, FILE *stream, int err)
{
    fprintf(stream,
            "Usage: %s INPUT\n"
            "Read from INPUT file and write the result to the program directory.\n\n"
            "INPUT is a required positional argument.\n"
            "Example:\n"
            "  %s ./input.txt\n",
            progname, progname);
    exit(err);
}

static void
ensure_exclusive_cli_options(const char *progname,
                             const char *arg,
                             struct montrer_args args)
{
    if (args.help || args.version || args.in_filepath) {
        fprintf(stderr, "Conflicting option: %s\n", arg);
        usage(progname, stderr, EXIT_FAILURE);
    }
}

int
main(int argc, char **argv)
{
    struct montrer_args args = {0};

    if (argc < 2)
        usage(argv[0], stderr, EXIT_FAILURE);

    for (int i = 1; i < argc; ++i) {
        const char *arg = argv[i];

        if (STRCMP_LIT(arg, "--help") == 0 || STRCMP_LIT(arg, "-h") == 0) {
            ensure_exclusive_cli_options(argv[0], arg, args);
            args.help = 1;
        } else if (STRCMP_LIT(arg, "--version") == 0
                   || STRCMP_LIT(arg, "-v") == 0) {
            ensure_exclusive_cli_options(argv[0], arg, args);
            args.version = 1;
        } else if (arg[0] != '-') {
            ensure_exclusive_cli_options(argv[0], arg, args);
            args.in_filepath = arg;
        } else {
            fprintf(stderr, "Unknown argument: %s\n", arg);
            usage(argv[0], stderr, EXIT_FAILURE);
        }
    }

    if (args.help)
        usage(argv[0], stdout, EXIT_SUCCESS);

    if (args.version) {
        version_info(stdout, argv[0]);
        exit(EXIT_SUCCESS);
    }

    {
        FILE *in_fp, *out_fp;
        uint32_t line, slide;
        char current_line[MAX_LINE_SIZE], previous_line[MAX_LINE_SIZE];

        in_fp = fopen(args.in_filepath, "r");
        if (in_fp == NULL)
            PANIC("fopen(%s): %s", args.in_filepath, strerror(errno));

        if (fgets(previous_line, MAX_LINE_SIZE, in_fp) == NULL)
            PANIC("error: file too short!");

        out_fp = NULL;
        line = slide = 0;
        while (fgets(current_line, MAX_LINE_SIZE, in_fp) != NULL) {            
            if (is_unichar(current_line, '=')) {
                // Case if heading 1 is found
                char filename[MAX_FILENAME];
                char *trimmed_line;

                printf("h1> %s", previous_line);

                /* In the case where a new heading, i.e., a new slide is
                   encountered and we are working on the old file, we gracefully
                   write the HTML footer and close the file. */
                if (out_fp != NULL) {
                    write_slide_footer(out_fp);
                    fclose(out_fp);
                }

                snprintf(filename, sizeof(filename), "slide-%03d.html", ++slide);

                out_fp = fopen(filename, "w");
                if (out_fp == NULL)
                    PANIC("fopen(%s): %s\n", filename, strerror(errno));

                trimmed_line = strtrim(previous_line);
                write_slide_header(out_fp, trimmed_line, slide);
                fprintf(out_fp, "\t\t<h1>%s</h1>", trimmed_line);
            } else if (is_unichar(current_line, '-')) {
                // Case if heading 2 is found
                printf("h2> %s", previous_line);
                fprintf(out_fp, "\t<h2>%s</h2>\n", strtrim(previous_line));
            } else {
                if (!is_unichar(previous_line, '=')
                    && !is_unichar(previous_line, '-')
                    && strlen(previous_line) > 1) {
                    if (previous_line[0] == '+') {
                        printf("li> %s", previous_line);
                        fprintf(out_fp, "\t\t<li>%s</li>\n", strtrim(previous_line));
                    } else  {
                        printf("> %s", previous_line);
                        fprintf(out_fp, "\t\t<p>%s</p>\n", strtrim(previous_line));
                    }
                }
            }

            strcpy(previous_line, current_line);
            ++line;
        }

        if (out_fp != NULL)
            write_slide_footer(out_fp);
    }

    return 0;
}
