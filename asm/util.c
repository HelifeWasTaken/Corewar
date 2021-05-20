/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** util
*/

#include <corewar/asm.h>

bool is_special_opcode(BYTE opcode)
{
    return (opcode == LIVE_OPCODE || opcode == ZJMP_OPCODE ||
            opcode == FORK_OPCODE || opcode == LFORK_OPCODE);
}

uint32_t count_byte_instruction_size(instruction_t *instruction)
{
    uint32_t size = 1;

    size += is_special_opcode(instruction->opcode) ? 0 : 1;
    for (uint8_t i = 0; i < instruction->arg_count; i++) {
        if ((OP_TAB[instruction->opcode - 1].type[i] & T_IDX) != 0) {
            size += IND_SIZE;
            continue;
        }
        if (instruction->param[i].type == T_IND) {
            size += IND_SIZE;
            continue;
        }
        if (instruction->param[i].type == T_REG) {
            size += 1;
            continue;
        }
        size += DIR_SIZE;
    }
    return (size);
}
