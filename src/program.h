#ifndef PROGRAM_H
#define PROGRAM_H

#define MAX_PROG_LEN 4096
#define TAPE_SIZE 30000


#include <stdint.h>


typedef struct
{
    uint8_t     reg;
    uint8_t     reg_empty;
    size_t      len;
    uint8_t*    tape;
    char**      program;
} Program;

typedef struct
{
    size_t  pc;
    int     dp;
} Registers;

typedef enum
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
} OpCodes;


void run(Program* p, Registers* reg);
uint8_t get_op_from_str(char* str);
Program* create_prog_from_file(char* filename);
void free_program(Program* p);

#endif  // PROGRAM_H

