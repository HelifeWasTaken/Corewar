/*
** EPITECH PROJECT, 2021
** op
** File description:
** Minishell
*/

#ifndef _COREWAR_OP_H_
    #define _COREWAR_OP_H_

    #define MEM_SIZE            (6 * 1024)
    #define IDX_MOD             512
    #define MAX_ARGS_NUMBER     4

    #define COMMENT_CHAR        '#'
    #define LABEL_CHAR          ';'
    #define DIRECT_CHAR         '%'
    #define SEPARATOR_CHAR      ','

    #define LABEL_CHARS         "abcdefghijklmnopqrstuvwxyz_0123456789"

    #define NAME_CMD_STRING     ".name"
    #define COMMENT_CMD_STRING  ".comment"

    #define REG_NUMBER          16

    #define T_REG               1
    #define T_DIR               2
    #define T_IND               4

    #define  T_LAB              8

    typedef struct op_s {
        char *mnemonique;
        char nbr_args;
        args_type_t type[MAX_ARGS_NUMBER];
        char code;
        int nbr_cycles;
        char *comment;
    } op_t;

    #define IND_SIZE            2
    #define DIR_SIZE            4
    #define REG_SIZE            DIR_SIZE

    #define PROG_NAME_LENGTH    128
    #define COMMENT_LENGTH      2048

    #define COREWAR_EXEC_MAGIC  0xea83f3

    typedef struct header_s {
        int magic;
        char prog_name[PROG_NAME_LENGTH + 1];
        int prog_size;
        char comment[COMMENT_LENGTH + 1];
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
