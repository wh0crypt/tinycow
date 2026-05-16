// https://esolangs.org/wiki/COW

#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#define MAX_PROG_LEN 4096


typedef struct
{
    char*   program[MAX_PROG_LEN];
    size_t  len;
} Program;

enum
{
    JUMP_START      = 0x00,
    BACK            = 0x01,
    FORWARD         = 0x02,
    EXEC            = 0x03,
    IO_IF_ZERO      = 0x04,
    DEC             = 0x05,
    INC             = 0x06,
    JUMP_IF_ZERO    = 0x07,
    SET_ZERO        = 0x08,
    COPY_REG        = 0x09,
    PRINT_INT       = 0x0A,
    READ_INT        = 0x0B,
    INV             = 0xFF
} Instruction;


void run(Program* program);
uint8_t get_op_from_str(char* str);
Program create_prog_from_file(char* filename);
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

    Program p = create_prog_from_file(argv[0]);
    if (p.len == 0)
    {
        fprintf(stderr, "error: program is empty\n");
        return 1;
    }

    run(&p);
    return 0;
}


#define ASSERT_TAPE_FULL()                          \
    do                                              \
    {                                               \
        if (dp >= (MAX_PROG_LEN - 1)) {             \
            fprintf(stderr, "error: tape full\n");  \
            return;                                 \
        }                                           \
    } while (0)

#define ASSERT_TAPE_EMPTY()                             \
    do                                                  \
    {                                                   \
        if (dp <= 0)                                    \
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

void run(Program* program)
{
    uint16_t pc         = 0;
    int      dp         = 0;
    uint8_t  reg        = 0;
    uint8_t  reg_empty  = 1;
    uint8_t  tape[MAX_PROG_LEN];

    while (pc < program->len)
    {
        uint8_t opcode = get_op_from_str(program->program[pc]);
        SWITCH:
        switch (opcode)
        {
            case JUMP_START:
                // TODO
                break;
            case BACK:
                ASSERT_TAPE_EMPTY();
                --dp; ++pc;
                break;
            case FORWARD:
                ASSERT_TAPE_FULL();
                ++dp; ++pc;
                break;
            case EXEC:
                if (tape[dp] > READ_INT || tape[dp] == EXEC)
                {
                    fprintf(stderr, "error: invalid EXEC instruction '0x%02x' at '0x%02x'\n", tape[dp], pc);
                    exit(1);
                }
                opcode = tape[dp];
                goto SWITCH;
                break;
            case IO_IF_ZERO:
                if (tape[dp] == 0) tape[dp] = (uint8_t)getchar();
                else putchar(tape[dp]);
                break;
            case DEC:
                --tape[dp]; ++pc;
                break;
            case INC:
                ++tape[dp]; ++pc;
                break;
            case JUMP_IF_ZERO:
                // TODO
                break;
            case SET_ZERO:
                tape[dp] = 0; ++pc;
                break;
            case COPY_REG:
                if (reg_empty == 1)
                {
                    reg = tape[dp];
                    reg_empty = 0;
                }
                else
                {
                    tape[dp] = reg;
                    reg_empty = 1;
                }
                ++pc;
                break;
            case PRINT_INT:
                printf("%d", tape[dp]); ++pc;
                break;
            case READ_INT:
                scanf("%" SCNu8, tape + dp); ++pc;
                break;
            default: ++pc;
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

Program create_prog_from_file(char* filename)
{
    Program prog = {{""}, 0};

    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "error: file '%s' cannot be opened.\n", filename);
        return prog;
    }

    char content[MAX_PROG_LEN];
    fgets(content, MAX_PROG_LEN, fp);
    memcpy(prog.program, content, strlen(content) * sizeof(char));
    prog.len = strlen(content);
    return prog;
}

void show_usage()
{
    printf("Usage: tinycow [-h|--help] <FILE>\nTry 'tinycow --help' for more information.\n");
}

void show_help()
{
    // TODO: print an actual help message
}

