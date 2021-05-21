/*
** EPITECH PROJECT, 2021
** opcode
** File description:
** parse
*/

#include <corewar/asm.h>

bool parse_opcode(parser_t *parser, char *buffer, instruction_t *ins)
{
    size_t size;

    skip_spaces(parser, buffer);
    for (size_t i = 0; i < ARRAY_SIZE(OP_TAB); i++) {
        size = estrlen(OP_TAB[i].mnemonique);
        if (estrncmp(&buffer[parser->col], OP_TAB[i].mnemonique, size) == 0 &&
                is_token(buffer[parser->col + size], " \t")) {
            parser->col += size;
            ins->opcode = OP_TAB[i].code;
            return (true);
        }
    }
    efprintf(stderr, "Opcode not recognized on line: %d\n", parser->line);
    return (false);
}
