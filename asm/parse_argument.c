/*
** EPITECH PROJECT, 2021
** parse
** File description:
** arguments
*/

#include <corewar/asm.h>

bool parse_argument(parser_t *parser, char *buffer, instruction_t *ins)
{
    skip_spaces(parser, buffer);
    if (buffer[parser->col] == 'r') {
        parser->col++;
        return (parse_register(parser, buffer, ins));
    }
    if (buffer[parser->col] == '%') {
        if (buffer[parser->col + 1] == ':') {
            parser->col += 2;
            return (parse_label_asm(parser, buffer, ins, true));
        } else {
            parser->col += 1;
            return (parse_value(parser, buffer, ins, true));
        }
    }
    if (buffer[parser->col] == ':') {
        parser->col++;
        return (parse_label_asm(parser, buffer, ins, false));
    } else if (eis_num(buffer[parser->col]))
        return (parse_value(parser, buffer, ins, false));
    efprintf(stderr, "Invalid char: %c at %d:%d\n", buffer[parser->col],
            parser->line, parser->col);
    return (false);
}
