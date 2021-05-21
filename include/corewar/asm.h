/*
** EPITECH PROJECT, 2021
** asm
** File description:
** asm
*/

#ifndef __ASM__COREWAR__H__
    #define __ASM__COREWAR__H__

    #include <corewar/op.h>
    #include <stdbool.h>
    #include <erty/eprintf.h>
    #include <erty/estdlib.h>
    #include <erty/egetline.h>

    enum {
        FAILURE = false,
        SUCESS_INSTRUCTION = 1,
        EMPTY_LINE = 2,
        ONLY_LABEL = 3
    };

    typedef struct instruction {
        struct {
            union {
                int32_t iv;
                char *is;
            };
            int16_t type;
            bool is_jump_not_complete;
        } param[3];
        BYTE opcode;
        uint8_t arg_count;
        struct instruction *next;
    } instruction_t;

    void instruction_push_back(instruction_t **head, struct instruction *data);

    typedef struct label {
        char *name;
        uint64_t index;
        struct label *next;
    } label_t;

    struct label *get_label(struct label *head, char *search);
    void label_push_back(struct label **head, struct label *data);

    typedef struct parser {
        struct instruction *instruction;
        struct label *label;
        uint64_t mem_index;
        uint64_t line;
        uint64_t col;
        struct header_s header;
    } parser_t;


    void compiler_internal(parser_t *parser, int fd);

    void skip_spaces(parser_t *parser, char *buffer);
    bool is_token(char const c, char const *tokens);

    bool parse_opcode(parser_t *parser, char *buffer, instruction_t *ins);
    bool parse_label(parser_t *parser, char *buffer);
    bool parse_label_asm(parser_t *parser, char *buffer, instruction_t *ins,
        bool is_direct);
    bool label_replacement(parser_t *parser);

    bool parse_value(parser_t *parser, char *buffer, instruction_t *ins,
        bool is_direct);
    bool parse_argument(parser_t *parser, char *buffer, instruction_t *ins);
    bool parse_register(parser_t *parser, char *buffer, instruction_t *ins);

    int parse_line(parser_t *parser, char *buffer, instruction_t *ins);
    bool parser_line_error(parser_t *parser, char *buffer,
            instruction_t *ins);

    bool read_header(parser_t *parser, int fd);
    char *read_quotes(parser_t *parser, char *buffer, bool is_name);

    int open_file(char const *file);

    bool is_special_opcode(BYTE opcode);
    uint32_t count_byte_instruction_size(instruction_t *instruction);
    bool pre_parsing(parser_t *parser, int fd);

    #define USAGE "USAGE./asm file_name[.s]\n" \
        "DESCRIPTION\n\tfile_namefile in assembly language to be converted " \
        "into file_name.cor,an executable in the Virtual Machine.\n"

    #define COL_BUFSIZE(buffer, parser) (estrlen(buffer) <= (parser).col)

#endif
