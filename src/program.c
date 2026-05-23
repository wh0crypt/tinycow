#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "program.h"


#define ASSERT_TAPE_FULL()                          \
    do                                              \
    {                                               \
        if (reg->dp >= TAPE_SIZE - 1)               \
        {                                           \
            fprintf(stderr, "error: tape full\n");  \
            return;                                 \
        }                                           \
    } while (0)

#define ASSERT_TAPE_EMPTY()                             \
    do                                                  \
    {                                                   \
        if (reg->dp <= 0)                               \
        {                                               \
            fprintf(stderr, "error: tape empty\n");     \
            return;                                     \
        }                                               \
    } while (0)

#define ASSERT_PC_OUTBOUND(pc, len)                                                         \
    do                                                                                      \
    {                                                                                       \
        if (pc >= len)                                                                      \
        {                                                                                   \
            fprintf(stderr, "error: pc value '%02lx' out-of-bounds (%02lx)\n", pc, len);    \
            return;                                                                         \
        }                                                                                   \
    } while (0)

void run(Program* p, Registers* reg)
{
    while (reg->pc < p->len)
    {
        uint8_t opcode = get_op_from_str(p->program[reg->pc]);
        SWITCH:
        switch (opcode)
        {
            case JUMP_START:
                // TODO
                break;
            case BACK:
                ASSERT_TAPE_EMPTY();
                --reg->dp; ++reg->pc;
                break;
            case FORWARD:
                ASSERT_TAPE_FULL();
                ++reg->dp; ++reg->pc;
                break;
            case EXEC:
                if (p->tape[reg->dp] > READ_INT || p->tape[reg->dp] == EXEC)
                {
                    fprintf(stderr, "error: invalid EXEC instruction '0x%02x' at '0x%02lx'\n", p->tape[reg->dp], reg->pc);
                    exit(1);
                }
                opcode = p->tape[reg->dp];
                goto SWITCH;
                break;
            case IO_IF_ZERO:
                if (!p->tape[reg->dp]) p->tape[reg->dp] = (uint8_t)getchar();
                else putchar(p->tape[reg->dp]);
                ++reg->pc;
                break;
            case DEC:
                --p->tape[reg->dp]; ++reg->pc;
                break;
            case INC:
                ++p->tape[reg->dp]; ++reg->pc;
                break;
            case JUMP_IF_ZERO:
                // TODO
                break;
            case SET_ZERO:
                p->tape[reg->dp] = 0; ++reg->pc;
                break;
            case COPY_REG:
                if (p->reg_empty == 1)
                {
                    p->reg = p->tape[reg->dp];
                    p->reg_empty = 0;
                }
                else
                {
                    p->tape[reg->dp] = p->reg;
                    p->reg_empty = 1;
                }
                ++reg->pc;
                break;
            case PRINT_INT:
                printf("%d", p->tape[reg->dp]); ++reg->pc;
                break;
            case READ_INT:
                scanf("%" SCNu8, p->tape + reg->dp); ++reg->pc;
                break;
            default: ++reg->pc;
        }
    }
}

uint8_t get_op_from_str(char* str)
{
    if (!strcmp(str, "moo")) return JUMP_START;
    if (!strcmp(str, "mOo")) return BACK;
    if (!strcmp(str, "moO")) return FORWARD;
    if (!strcmp(str, "mOO")) return EXEC;
    if (!strcmp(str, "Moo")) return IO_IF_ZERO;
    if (!strcmp(str, "MOo")) return DEC;
    if (!strcmp(str, "MoO")) return INC;
    if (!strcmp(str, "MOO")) return JUMP_IF_ZERO;
    if (!strcmp(str, "OOO")) return SET_ZERO;
    if (!strcmp(str, "MMM")) return COPY_REG;
    if (!strcmp(str, "OOM")) return PRINT_INT;
    if (!strcmp(str, "oom")) return READ_INT;
    return INV;
}

Program* create_prog_from_file(char* filename)
{
    FILE* fp = fopen(filename, "r");
    if (!fp)
    {
        fprintf(stderr, "error: file '%s' cannot be opened.\n", filename);
        exit(1);
    }

    size_t len = 0;
    char content[MAX_PROG_LEN][4];
    while (fscanf(fp, "%3s", content[len]) == 1 && len < MAX_PROG_LEN) ++len;
    fclose(fp);

    Program* p = malloc(sizeof(Program));
    if (!p) return NULL;

    p->program = malloc(len * sizeof(char*));
    p->tape = calloc(TAPE_SIZE, sizeof(uint8_t));

    if (!p->program || !p->tape)
    {
        free_program(p);
        return NULL;
    }

    for (size_t i = 0; i < len; ++i)
    {
        p->program[i] = malloc(4);
        if (!p->program[i])
        {
            for (size_t j = 0; j < i; ++j) free(p->program[j]);
            free(p->program);
            free(p->tape);
            free(p);
            return NULL;
        }
        memcpy(p->program[i], content[i], 4);
    }

    p->len = len;
    p->reg_empty = 1;
    p->reg = 0;
    return p;
}

void free_program(Program* p)
{
    if (!p) return;
    if (p->program)
    {
        for (size_t i = 0; i < p->len; ++i) free(p->program[i]);
        free(p->program);
    }
    free(p->tape);
    free(p);
}

