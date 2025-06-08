#ifndef ARGS_H
#define ARGS_H

struct montrer_args { const char *in_filepath; };

/* Parse the program arguments and initialize it into struct montrer_args */
struct montrer_args parse_args (int argc, char **argv);

#endif //ARGS_H

