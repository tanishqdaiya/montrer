/* montrer.c -- Transforms structured mardown into something better: a full set
   of clean and minimal HTML slides that you can use to present your ideas.
   Author: Tanishq Daiya <tanishqdaiya@yahoo.com>

   This file is a part of montrer (https://github.com/tanishqdaiya/montrer)

   montrer is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   See <https://www.gnu.org/licenses/> for details. */

#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 1024

/* Provided the program name, this function prints the help message describing
   the usage of the program */
static void
usage (const char *progname)
{
  fprintf (stderr,
           "Usage: %s INPUT\n"
           "Read from INPUT file and write the result to the program directory.\n\n"
           "INPUT is a required positional argument.\n"
           "Example:\n"
           "  %s ./input.txt\n",
           progname, progname);

  exit (EXIT_FAILURE);
}

/* Checks if the provided line contains only the given character c */
static bool
line_only_contains (char line[], char c)
{
  int i = 0;
  while (line[i] != '\n' && line[i] != '\0')
    if (line[i++] != c)
      return false;

  if (i < 1)
    return false;

  return true;
}

/* Trims a whitespaces, tabs and newlines from the start and end of a string
   without allocating additional memory */
static char *
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

int
main (int argc, char **argv)
{
  const char *in_path = NULL;

  if (argc < 2)
    usage (argv[0]);

  in_path = argv[1];
  if (!in_path)
    usage (argv[0]);

  FILE *in_fp = fopen (in_path, "r");
  if (in_fp == NULL)
    {
      fprintf (stderr, "fopen(%s): %s\n", in_path, strerror(errno));
      exit (EXIT_FAILURE);
    }

  char curr_line[MAX_LINE_SIZE];
  char prev_line[MAX_LINE_SIZE];
  int line = 0;

  if (fgets (prev_line, MAX_LINE_SIZE, in_fp) == NULL)
    {
      fprintf (stderr, "File should contain more lines");
      exit (EXIT_FAILURE);
    }


  FILE *out_fp = NULL;
  int slide = 0;
  while (fgets (curr_line, MAX_LINE_SIZE, in_fp) != NULL)
    {
      if (line_only_contains (curr_line, '='))
        {
          printf ("h1:%s", prev_line);

          if (out_fp)
            {
              fprintf (out_fp, "</main>\n"
                       "<script src=\"./script.js\"></script>\n"
                       "</body>\n"
                       "</html>");
              fclose (out_fp);
            }

          char filename[MAX_LINE_SIZE];
          snprintf (filename, sizeof (filename), "Slide_%d.html", ++slide);

          out_fp = fopen (filename, "w");
          if (!out_fp)
            {
              perror ("fopen");
              fclose (in_fp);
              return (EXIT_FAILURE);
            }

          const char *trimmed = trim (prev_line);

          /* @Implementation Write an HTML template engine rather later */
          fprintf (out_fp, "<!DOCTYPE html>\n"
                   "<html lang=\"en\">\n"
                   "<head>\n"
                   "<meta charset=\"UTF-8\" />\n"
                   "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\" />\n"
                   "<title>Montrer</title>\n"
                   "<link rel=\"stylesheet\" type=\"text/css\" href=\"styles.css\" />\n"
                   "<link rel=\"icon\" href=\"favicon.png\" />\n"
                   "</head>\n"
                   "<body>\n"
                   "<header>\n"
                   "<nav id=\"controls\">\n"
                   "<ul>\n"
                   "<li><a id=\"prev\" href=\"Slide_%d.html\">Prev</a></li>\n"
                   "<li><a aria-current=\"page\" href=\"#\">[%d] %s</a></li>\n"
                   "<li><a id=\"next\" href=\"Slide_%d.html\">Next</a></li>\n"
                   "</ul>\n"
                   "</nav>\n"
                   "</header>\n"
                   "<main>\n", slide - 1, slide, trimmed, slide + 1);
          fprintf (out_fp, "<h1>%s</h1>\n", trimmed);
        }

      else if (line_only_contains (curr_line, '-'))
        {
          printf ("h2:%s", prev_line);
          fprintf (out_fp, "<h2>%s</h2>\n", trim (prev_line));
        }

      else
        {
          if (!line_only_contains (prev_line, '=')
              && !line_only_contains (prev_line, '-')
              && strlen (prev_line) > 1)
            {
              printf ("li:%s", prev_line);
              fprintf(out_fp, "<li>%s</li>\n", trim (prev_line));
            }
        }

      strcpy (prev_line, curr_line);
      line++;
    }

  if (out_fp != NULL)
    {
      fprintf (out_fp, "</main>\n"
               "<script src=\"./script.js\"></script>\n"
               "</body>\n"
               "</html>");
      fclose (out_fp);
    }

  return 0;
}
