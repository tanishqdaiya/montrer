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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 1024
#define MAX_FILENAME 64

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

/* Checks if the provided line contains only the given character c (unichar) */
static bool
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

static FILE *
open_file (const char *path, const char *mode)
{
  FILE *fp = fopen (path, mode);
  if (fp == NULL)
    {
      fprintf (stderr, "fopen(%s): %s\n", path, strerror(errno));
      exit (EXIT_FAILURE);
    }

  return fp;
}

struct montrer_args { const char *in_filepath; };

static struct montrer_args
parse_args (int argc, char **argv)
{
  struct montrer_args args = { 0 };
  args.in_filepath = argv[1];
  
  if (argc < 2 || args.in_filepath == NULL)
    usage (argv[0]);

  return args;
}

/* Writes the header template for each Slide_#.html to a given file */
/* @Implement HTML template engine rather than this */
static void
write_slide_header (FILE *out_file, const char *slide_name, uint8_t slide_no)
{
  fprintf (out_file, "<!DOCTYPE html>\n"
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
	   "<main>\n", slide_no - 1, slide_no, slide_name, slide_no + 1);
 }

/* Writes the footer template for each Slide_#.html and closes the given file */
static void
write_slide_footer (FILE *out_file)
{
  fprintf (out_file, "</main>\n"
	   "<script src=\"./script.js\"></script>\n"
	   "</body>\n"
	   "</html>");
  fclose (out_file);
}

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
