/*
** EPITECH PROJECT, 2021
** op
** File description:
** Minishell
*/

#ifndef _COREWAR_OP_H_
    #define _COREWAR_OP_H_

    #include <stdint.h>

    #define BYTE char

    union int_byte {
        int nb;
        BYTE s[4];
    };

    #define LABEL_CHARS         "abcdefghijklmnopqrstuvwxyz_0123456789"
    #define NAME_CMD_STRING     ".name"
    #define COMMENT_CMD_STRING  ".comment"

    // Mem size is equivalent to 6 * 1024

    enum {
        MEM_SIZE = 6144,
        IDX_MOD = 512,
        MAX_ARGS_NUMBER = 4,
        CHAMPION_COUNT_MAX = MAX_ARGS_NUMBER,
        REG_NUMBER = 16,
        COMMENT_CHAR = '#',
        LABEL_CHAR = ';',
        DIRECT_CHAR = '%',
        SEPARATOR_CHAR = ',',
        T_REG = 1,
        T_DIR = 2,
        T_IND = 4,
        T_LAB = 8,
        IND_SIZE = 2,
        DIR_SIZE = 4,
        REG_SIZE = DIR_SIZE,
        PROG_NAME_LENGTH = 128,
        COMMENT_LENGTH = 2048,
        COREWAR_EXEC_MAGIC = 0xea83f3,
        MAGIC_NUMBER = COREWAR_EXEC_MAGIC,
        HEADER_SIZE = PROG_NAME_LENGTH + COMMENT_LENGTH + sizeof(int) * 2 + 2
    };

    typedef struct op_s {
        char *mnemonique;
        char nbr_args;
        BYTE type[MAX_ARGS_NUMBER];
        BYTE code;
        int nbr_cycles;
        char *comment;
    } op_t;

    typedef struct header_s {
        uint32_t magic;
        BYTE prog_name[PROG_NAME_LENGTH + 1];
        uint32_t prog_size;
        BYTE comment[COMMENT_LENGTH + 1];
    } header_t;

    static const struct op_s OP_TAB[] = {
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
        {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero"},
        {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
            "load index"},
        {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
            "store index"},
        {"fork", 1, {T_DIR}, 12, 800, "fork"},
        {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load"},
        {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
            "long load index"},
        {"lfork", 1, {T_DIR}, 15, 1000, "long fork"},
        {"aff", 1, {T_REG}, 16, 2, "aff"},
        {0, 0, {0}, 0, 0, 0}
    };

#endif
