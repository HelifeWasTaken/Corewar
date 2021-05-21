/*
** EPITECH PROJECT, 2021
** parser_error
** File description:
** parser_line_error
*/

#include "corewar/asm.h"

bool parser_line_error(parser_t *parser, char *buffer,
        instruction_t *ins)
{
    skip_spaces(parser, buffer);
    if (ins->arg_count >= 3) {
        efprintf(stderr, "Expected end of line at: %d:%d\n",
                parser->line, parser->col);
        return (false);
    }
    if (buffer[parser->col] != ',' && ins->arg_count != 0) {
        efprintf(stderr, "Missing ',' at %d:%d\n",
                parser->line, parser->col);
        return (false);
    }
    if (ins->arg_count != 0)
        parser->col++;
    if (parse_argument(parser, buffer, ins) == false)
        return (false);
    return (true);
}