/*
** EPITECH PROJECT, 2021
** parser
** File description:
** line
*/

#include "corewar/asm.h"

static struct instruction *instruction_node(struct instruction *data)
{
    struct instruction *new = ecalloc(sizeof(struct instruction), 1);

    new->arg_count = data->arg_count;
    new->opcode = data->opcode;
    for (uint8_t i = 0; i < data->arg_count; i++)
        new->param[i] = data->param[i];
    new->next = NULL;
    return (new);
}

void instruction_push_back(instruction_t **head, struct instruction *data)
{
    struct instruction *ptr = *head;

    if (ptr == NULL) {
        *head = instruction_node(data);
        return;
    }
    for (; ptr->next; ptr = ptr->next);
    ptr->next = instruction_node(data);
}

static bool parse_line_check_end(parser_t *parser, char *buffer)
{
    if (buffer[parser->col] != '\0' && buffer[parser->col] != '#') {
        efprintf(stderr, "Unexpected char: %c at %d:%d", buffer[parser->col],
                parser->line, parser->col);
        return (false);
    }
    return (true);
}

static bool parse_line_get_arguments(parser_t *parser, char *buffer,
        instruction_t *ins)
{
    skip_spaces(parser, buffer);
    if (buffer[parser->col] == '\0' || buffer[parser->col] == '#') {
        if (ins->arg_count == 0) {
            efprintf(stderr, "Expected at least one argument at: %d:%d\n",
                    parser->line, parser->col);
            return (false);
        }
        return (true);
    }
    if (parser_line_error(parser, buffer, ins) == false)
        return (false);
    ins->arg_count++;
    return (parse_line_get_arguments(parser, buffer, ins));
}

int parse_line(parser_t *parser, char *buffer, instruction_t *ins)
{
    *ins = (instruction_t){0};
    skip_spaces(parser, buffer);
    if (buffer[parser->col] == '#' || buffer[parser->col] == '\0')
        return (EMPTY_LINE);
    if (parse_label(parser, buffer) == false)
        return (false);
    skip_spaces(parser, buffer);
    if (buffer[parser->col] == '#' || buffer[parser->col] == '\0')
        return (EMPTY_LINE);
    if (parse_opcode(parser, buffer, ins) == false)
        return (false);
    if (parse_line_get_arguments(parser, buffer, ins) == false)
        return (false);
    return (parse_line_check_end(parser, buffer));
}
