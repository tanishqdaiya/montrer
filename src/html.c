#include <stdio.h>
#include <stdint.h>

#include "montrer.h"

void
write_slide_footer(FILE *file)
{
    fprintf(file,
            "</main>\n"
            "<script src=\"./script.js\"></script>\n"
            "</body>\n"
            "</html>");
}

void
write_slide_header(FILE *file, const char *slide_name, uint8_t n)
{
    fprintf(file,
            "<!DOCTYPE html>\n"
            "<html lang=\"en\">\n"
            "<head>\n"
            "\t<meta charset=\"UTF-8\" />\n"
            "\t<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\" />\n"
            "\t<title>Montrer</title>\n"
            "\t<link rel=\"stylesheet\" type=\"text/css\" href=\"styles.css\" />\n"
            "\t<link rel=\"icon\" href=\"favicon.png\" />\n"
            "</head>\n"
            "<body>\n"
            "\t<header>\n"
            "\t\t<nav id=\"controls\">\n"
            "\t\t\t<ul>\n"
            "\t\t\t\t<li><a id=\"prev\" href=\"slide-%03d.html\">Prev</a></li>\n"
            "\t\t\t\t<li><a aria-current=\"page\" href=\"#\">[%d] %s</a></li>\n"
            "\t\t\t\t<li><a id=\"next\" href=\"slide-%03d.html\">Next</a></li>\n"
            "\t\t\t</ul>\n"
            "\t\t</nav>\n"
            "\t</header>\n"
            "\t<main>\n", n - 1, n, slide_name, n + 1);
}
