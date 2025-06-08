#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "io.h"

/* Opens a given file and does the necessary checks */
FILE *
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

/* Writes the header template for each Slide_#.html to a given file */
/* @Implement HTML template engine rather than this */
void
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
void
write_slide_footer (FILE *out_file)
{
  fprintf (out_file, "</main>\n"
	   "<script src=\"./script.js\"></script>\n"
	   "</body>\n"
	   "</html>");
  fclose (out_file);
}
