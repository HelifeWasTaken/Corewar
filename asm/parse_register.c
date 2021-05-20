/*
** EPITECH PROJECT, 2021
** parse
** File description:
** register
*/

#include <corewar/asm.h>

static bool parser_register_error(parser_t *parser,
        char *buffer, size_t *i)
{
    if (eis_num(buffer[parser->col]) == false) {
        efprintf(stderr, "Invalid numeric value on %d:%d",
                parser->col, parser->line);
        return (false);
    }
    for (; !istoken(buffer[*i], ", #") && buffer[*i]; (*i)++)
        if (eis_num(buffer[*i]) == false) {
            efprintf(stderr, "Invalid numeric value on %d:%d",
                    parser->line, *i);
            return (false);
        }
    return (true);
}

bool parse_register(parser_t *parser, char *buffer, instruction_t *ins)
{
    size_t i = parser->col;

    skip_spaces(parser, buffer);
    if (parser_register_error(parser, buffer, &i) == false)
        return (false);
    ins->param[ins->arg_count].type = T_REG;
    ins->param[ins->arg_count].iv = eatol(&buffer[parser->col]).value;
    if (ins->param[ins->arg_count].iv < 1 ||
            ins->param[ins->arg_count].iv > REG_NUMBER) {
        efprintf(stderr, "Invalid reg number: %d at %d:%d\n",
                ins->param[ins->arg_count].iv, parser->line, parser->col);
        return (false);
    }
    parser->col = i;
    return (true);
}
