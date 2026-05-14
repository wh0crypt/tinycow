// https://esolangs.org/wiki/COW

#include <stdio.h>
#include <stdint.h>
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
    UNK             = 0xFF
} Instruction;


uint8_t get_op_from_str(char* str);


int main()
{
    return 0;
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
    return UNK;
}

