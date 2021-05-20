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

uint32_t count_byte_instruction_size_dir(int32_t value)
{
    if (value < 0) {
        return (4);
    } else {
        if (value <= 0xff)
            return (1);
        if (value <= 0xff << 8)
            return (2);
        if (value <= 0xff << 16)
            return (3);
        return (4);
    }
}

uint32_t count_byte_instruction_size(instruction_t *instruction)
{
    uint32_t size = BASIC_SIZE_OPCODE_AND_LAYOUT;

    if (is_special_opcode(instruction->opcode))
        return (5);
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
