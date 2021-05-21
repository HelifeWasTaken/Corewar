/*
** EPITECH PROJECT, 2021
** is
** File description:
** token
*/

#include <corewar/asm.h>

bool is_token(char const c, char const *tokens)
{
    for (size_t i = 0; tokens[i]; i++)
        if (tokens[i] == c)
            return (true);
    return (false);
}

void skip_spaces(parser_t *parser, char *buffer)
{
    if (parser->col >= estrlen(buffer))
        return;
    for (; is_token(buffer[parser->col], " \t"); parser->col++);
}
