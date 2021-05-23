/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** op
*/

#include <corewar/op.h>
#include <erty/string/ecstring.h>
#include <erty/estdlib.h>

const struct op_s OP_TAB[OP_COUNT] = {
    {"live", 1, {T_DIR}, 1, 10, "alive"},
    {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load"},
    {"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store"},
    {"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition"},
    {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction"},
    {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
        "et (and  r1, r2, r3   r1&r2 -> r3"},
    {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
        "ou  (or   r1, r2, r3   r1 | r2 -> r3"},
    {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
        "ou (xor  r1, r2, r3   r1^r2 -> r3"},
    {"zjmp", 1, {T_DIR | T_IDX}, 9, 20, "jump if zero"},
    {"ldi", 3, {T_REG | T_DIR | T_IND | T_IDX,
        T_DIR | T_REG | T_IDX, T_REG}, 10, 25, "load index"},
    {"sti", 3, {T_REG, T_REG | T_DIR | T_IND | T_IDX,
        T_DIR | T_REG | T_IDX}, 11, 25, "store index"},
    {"fork", 1, {T_DIR | T_IDX}, 12, 800, "fork"},
    {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load"},
    {"lldi", 3, {T_REG | T_DIR | T_IND | T_IDX,
                    T_DIR | T_REG | T_IDX, T_REG}, 14, 50, "long load index"},
    {"lfork", 1, {T_DIR | T_IDX}, 15, 1000, "long fork"},
    {"aff", 1, {T_REG}, 16, 2, "aff"}
};

struct op_s get_op_from_opcode(BYTE opcode)
{
    return (OP_TAB[opcode - 1]);
}

struct op_s get_op_from_str(char *match)
{
    for (unsigned int i = 0; i < ARRAY_SIZE(OP_TAB); i++)
        if (estrcmp(match, OP_TAB[i].mnemonique) == 0)
            return (OP_TAB[i]);
    efprintf(stderr, "WARNING Undefined behaviour occured\n");
    return (OP_TAB[0]);
}
