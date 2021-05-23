/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** vm
*/

#include <corewar/vm.h>

bool has_coding_byte(BYTE opcode)
{
    return (!(opcode == LIVE_OPCODE || opcode == ZJMP_OPCODE ||
                opcode == FORK_OPCODE || opcode == LFORK_OPCODE));
}
