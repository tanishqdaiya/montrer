#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdint.h>

/* Opens a given file and does the necessary checks */
FILE *open_file (const char *path, const char *mode);

/* Writes the header template for each Slide_#.html to a given file */
void write_slide_header (FILE *out_file, const char *slide_name,
			 uint8_t slide_no);

/* Writes the footer template for each Slide_#.html and closes the given file */
void write_slide_footer (FILE *out_file);

#endif //IO_H
