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
#include <stdlib.h>
#include <string.h>

#include "args.h"
#include "io.h"
#include "str.h"

#define MAX_LINE_SIZE 1024
#define MAX_FILENAME 64

int
main (int argc, char **argv)
{
  struct montrer_args args = parse_args (argc, argv);

  char cur_line[MAX_LINE_SIZE];
  char prev_line[MAX_LINE_SIZE];
  FILE *in_fp = open_file (args.in_filepath, "r");
  if (fgets (prev_line, MAX_LINE_SIZE, in_fp) == NULL)
    {
      fprintf (stderr, "File should contain more lines\n");
      exit (EXIT_FAILURE);
    }

  FILE *out_fp = NULL;
  uint32_t line = 0;
  uint8_t slide = 0;
  while (fgets (cur_line, MAX_LINE_SIZE, in_fp) != NULL)
    {
      if (is_unichar (cur_line, '='))
        {
          printf ("h1:%s", prev_line);
          if (out_fp != NULL) write_slide_footer (out_fp);
	  
          char filename[MAX_FILENAME];
          snprintf (filename, sizeof (filename), "Slide_%d.html", ++slide);

	  out_fp = open_file (filename, "w");
          if (!out_fp) fclose (in_fp);

	  const char *trimmed_line = trim (prev_line);
	  write_slide_header (out_fp, trimmed_line, slide);
          fprintf (out_fp, "<h1>%s</h1>\n", trimmed_line);
        }

      else if (is_unichar (cur_line, '-'))
        {
          printf ("h2:%s", prev_line);
          fprintf (out_fp, "<h2>%s</h2>\n", trim (prev_line));
        }

      else
        {
          if (!is_unichar (prev_line, '=')
              && !is_unichar (prev_line, '-')
              && strlen (prev_line) > 1)
            {
              printf ("li:%s", prev_line);
              fprintf(out_fp, "<li>%s</li>\n", trim (prev_line));
            }
        }

      strcpy (prev_line, cur_line);
      line++;
    }

  if (out_fp != NULL)
    write_slide_footer (out_fp);

  return 0;
}
