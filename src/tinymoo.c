// https://esolangs.org/wiki/COW

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "program.h"

void show_usage();
void show_help();

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        show_usage();
        return EXIT_SUCCESS;
    }

    if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
    {
        show_help();
        return EXIT_FAILURE;
    }

    Program* p = create_prog_from_file(argv[1]);
    if (!p)
    {
        fprintf(stderr, "error: program is empty\n");
        return EXIT_FAILURE;
    }

    if (!p->len)
    {
        fprintf(stderr, "error: program is empty\n");
        free_program(p);
        return EXIT_FAILURE;
    }

    Registers* reg = malloc(sizeof(Registers));
    if (!reg)
    {
        fprintf(stderr, "error: could not create registers\n");
        free_program(p);
        return EXIT_FAILURE;
    }

    reg->pc = 0; reg->dp = 0;
    run(p, reg);
    free_program(p);
    free(reg);
    return EXIT_SUCCESS;
}


void show_usage()
{
    printf(
        "Usage: tinycow [-h|--help] <FILE>\n"
        "Try 'tinycow --help' for more information.\n"
    );
}

void show_help()
{
    printf(
        "tinycow -- a tiny virtual machine for the COW esoteric language.\n\n"
        "Usage: tinycow [-h|--help] <FILE>\n\n"
        "OPTIONS:\n"
        "    <FILE>\tSource file to execute.\n"
        "    -h, --help\tPrint this message.\n\n"
        "EXAMPLES:\n"
        "    tinycow --help\n"
        "    tinycow files/hello_world.cow\n"
    );
}

