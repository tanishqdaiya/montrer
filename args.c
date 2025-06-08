#include <stdio.h>
#include <stdlib.h>
#include "args.h"

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

struct montrer_args
parse_args (int argc, char **argv)
{
  struct montrer_args args = { 0 };
  args.in_filepath = argv[1];
  
  if (argc < 2 || args.in_filepath == NULL)
    usage (argv[0]);

  return args;
}
