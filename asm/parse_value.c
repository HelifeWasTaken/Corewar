/*
** EPITECH PROJECT, 2021
** parse
** File description:
** value
*/

#include <corewar/asm.h>

signed long long int get_value_overflow_warning(char *buffer, parser_t *parser,
        bool is_direct UNUSED)
{
    signed long long int value = 0;

    value = eatol(&buffer[parser->col]).value;
    return (value);
}

static bool parse_value_error(parser_t *parser, char *buffer, size_t *i)
{
    if (buffer[*i] == '-')
        (*i)++;
    if (eis_num(buffer[*i]) == false) {
        efprintf(stderr, "Invalid numeric value on %d:%d\n",
                parser->line, *i);
        return (false);
    }
    for (; !is_token(buffer[*i], ", #\t") && buffer[*i]; (*i)++) {
        if (eis_num(buffer[*i]) == false) {
            efprintf(stderr, "Invalid numeric value on %d:%d\n",
                    parser->line, *i);
            return (false);
        }
    }
    return (true);
}

bool parse_value(parser_t *parser, char *buffer, instruction_t *ins,
        bool is_direct)
{
    size_t i = parser->col;

    if (parse_value_error(parser, buffer, &i) == false)
        return (false);
    ins->param[ins->arg_count].type = is_direct ? T_DIR : T_IND;
    ins->param[ins->arg_count].iv =
        get_value_overflow_warning(buffer, parser, is_direct);
    parser->col = i;
    return (true);
}
