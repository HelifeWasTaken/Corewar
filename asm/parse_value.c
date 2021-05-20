/*
** EPITECH PROJECT, 2021
** parse
** File description:
** value
*/

#include <corewar/asm.h>

signed long long int get_value_overflow_warning(char *buffer, parser_t *parser,
        bool is_direct)
{
    signed long long int value = 0;

    value = eatol(&buffer[parser->col]).value;
    if (is_direct) {
        if (value > INT32_MAX || value < INT32_MIN) {
            efprintf(stderr, "Warning: Value exceed the size"
                    " of a direct value\n");
        }
    }
    if (value > INT16_MAX || value < INT16_MIN) {
        efprintf(stderr, "Warning: Value exceed the size"
                " of an indirect value\n");
    }
    return (value);
}

bool parse_value(parser_t *parser, char *buffer, instruction_t *ins,
        bool is_direct)
{
    size_t i = parser->col;

    if (buffer[i] == '-')
        i++;
    if (eis_num(buffer[i]) == false) {
            efprintf(stderr, "Invalid numeric value on %d:%d",
                    parser->line, parser->col);
        return (false);
    }
    for (; buffer[i] != ',' && buffer[i] && buffer[i] != '#' &&
            buffer[i] != ' '; i++) {
        if (eis_num(buffer[i]) == false) {
            efprintf(stderr, "Invalid numeric value on %d:%d",
                    parser->line, parser->col);
            return (false);
        }
    }
    ins->param[ins->arg_count].type = is_direct ? T_DIR : T_IND;
    ins->param[ins->arg_count].iv =
        get_value_overflow_warning(buffer, parser, is_direct);
    parser->col = i;
    return (true);
}
