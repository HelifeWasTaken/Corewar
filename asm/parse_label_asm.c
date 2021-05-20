/*
** EPITECH PROJECT, 2021
** parse_label_asm
** File description:
** corewar
*/

#include <corewar/asm.h>

bool parse_label_asm(parser_t *parser, char *buffer, instruction_t *ins,
        bool is_direct UNUSED)
{
    size_t i = parser->col;

    skip_spaces(parser, buffer);
    for (; buffer[i] && !istoken(buffer[i], ", #"); i++);
    ins->param[ins->arg_count].is_jump_not_complete = true;
    ins->param[ins->arg_count].is = estrndup(&buffer[parser->col],
            i - parser->col);
    ins->param[ins->arg_count].type = is_direct ? T_DIR : T_IND;
    parser->col = i;
    return (true);
}
