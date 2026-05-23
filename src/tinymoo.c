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
        return 0;
    }

    if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
    {
        printf("to be implemented\n"); // TODO: change to an actual help message
        return 0;
    }

    Program* p = create_prog_from_file(argv[1]);
    if (!p)
    {
        fprintf(stderr, "error: program is empty\n");
        return 1;
    }

    if (!p->len)
    {
        fprintf(stderr, "error: program is empty\n");
        free_program(p);
        return 1;
    }

    Registers* reg = malloc(sizeof(Registers));
    if (!reg)
    {
        fprintf(stderr, "error: could not create registers\n");
        free_program(p);
        return 1;
    }

    reg->pc = 0; reg->dp = 0;
    run(p, reg);
    free_program(p);
    free(reg);
    return 0;
}


void show_usage()
{
    printf("Usage: tinycow [-h|--help] <FILE>\nTry 'tinycow --help' for more information.\n");
}

void show_help()
{
    // TODO: print an actual help message
}

