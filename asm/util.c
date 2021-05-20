/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** util
*/

#include <corewar/asm.h>

static const uint32_t BASIC_SIZE_OPCODE_AND_LAYOUT = 2;

bool is_special_opcode(BYTE opcode)
{
    return (opcode == LIVE_OPCODE || opcode == ZJMP_OPCODE ||
            opcode == FORK_OPCODE || opcode == LFORK_OPCODE);
}

static uint32_t count_byte_instruction_size_special_opcode(instruction_t *ins)
{
    switch (ins->opcode) {
        case LIVE_OPCODE:
            return (DIR_SIZE + 1);
        case ZJMP_OPCODE:
        case FORK_OPCODE:
        case LFORK_OPCODE:
        default:
            return (IND_SIZE + 1);
    }
}

uint32_t count_byte_instruction_size(instruction_t *instruction)
{
    uint32_t size = BASIC_SIZE_OPCODE_AND_LAYOUT;

    if (is_special_opcode(instruction->opcode))
        return (count_byte_instruction_size_special_opcode(instruction));
    for (uint8_t i = 0; i < instruction->arg_count; i++) {
        switch (instruction->param[i].type) {
            case T_DIR:
                size += DIR_SIZE;
                break;
            case T_REG:
                size += 1;
                break;
            case T_IND:
                size += IND_SIZE;
                break;
            default:
                efprintf(stderr, "The impossible happened:"
                        "Undefined behaviour might occur\n");
        }
    }
    return (size);
}
