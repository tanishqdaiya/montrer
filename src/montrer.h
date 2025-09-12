#ifndef _MONTRER_H
#define _MONTRER_H

/* Arbitrary limits (user definable) */
#define MAX_LINE_SIZE (4096)
#define MAX_FILENAME (128)

/* Write HTML boilerplate header.
   file -- output stream
   slide_name -- title shown in slide navigation bar
   n -- slide number */
void write_slide_header(FILE *file, const char *slide_name, uint8_t n);

/* Write HTML footer to close the open tags */
void write_slide_footer(FILE *file);

#endif /*_MONTRER_H*/
