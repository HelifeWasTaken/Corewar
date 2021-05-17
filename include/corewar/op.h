/*
** EPITECH PROJECT, 2021
** op
** File description:
** Minishell
*/

#ifndef _COREWAR_OP_H_
    #define _COREWAR_OP_H_

    #include <stdint.h>

    #define BYTE unsigned char

    union int_byte {
        int nb;
        BYTE s[4];
    };

    #define LABEL_CHARS         "abcdefghijklmnopqrstuvwxyz_0123456789"
    #define NAME_CMD_STRING     ".name"
    #define COMMENT_CMD_STRING  ".comment"

    enum {
        MEM_SIZE = 6 * 1024,
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
        NOT_A_PLAYER = -1,
        OP_COUNT = 0x10,
        HEADER_SIZE =   PROG_NAME_LENGTH + COMMENT_LENGTH +
                        sizeof(uint32_t) * 2 + 2
    };

    typedef struct op_s {
        const char *mnemonique;
        const uint8_t nbr_args;
        const BYTE type[MAX_ARGS_NUMBER];
        const BYTE code;
        const int nbr_cycles;
        const char *comment;
    } op_t;

    typedef struct header_s {
        uint32_t magic;
        BYTE prog_name[PROG_NAME_LENGTH + 1];
        uint32_t prog_size;
        BYTE comment[COMMENT_LENGTH + 1];
    } header_t;

    extern const struct op_s OP_TAB[OP_COUNT];

    typedef union mem_u16 mem16_t;
    typedef union mem_u32 mem32_t;
    typedef union mem_u64 mem64_t;

    union mem_u16 {
        uint16_t vi;
        BYTE vmem[sizeof(uint16_t)];
    };

    union mem_u32 {
        uint32_t vi;
        BYTE vmem[sizeof(uint32_t)];
    };

    union mem_u64 {
        uint64_t vi;
        BYTE vmem[sizeof(uint64_t)];
    };

#endif
