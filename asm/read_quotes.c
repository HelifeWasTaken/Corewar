/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** read_quotes
*/

#include "corewar/asm.h"

static char *process_read_quotes(parser_t *parser, char *buffer, bool is_name,
        char *ptr)
{
    char *new_ptr = estrndup(&buffer[parser->col],  ptr - &buffer[parser->col]);

    for (size_t i = 1; ptr[i] && ptr[i] != '#'; i++) {
        if (ptr[i] != ' ' && ptr[i] != '\t') {
            efree(new_ptr);
            efprintf(stderr, "Expected EOL at the end of the %s\n", is_name ?
                    "name" : "comment");
            return (NULL);
        }
    }
    return (new_ptr);
}

char *read_quotes(parser_t *parser, char *buffer, bool is_name)
{
    char *ptr = NULL;

    parser->col += is_name ? 5 : 8;
    skip_spaces(parser, buffer);
    if (buffer[parser->col] != '\"') {
        efprintf(stderr, "Missing quotes in the %s\n",
                is_name ? "name" : "comment");
        return (NULL);
    }
    parser->col++;
    ptr = estrchr(&buffer[parser->col], '\"');
    if (ptr == NULL) {
        efprintf(stderr, "Missing quotes in the %s\n",
                is_name ? "name" : "comment");
        return (NULL);
    }
    return (process_read_quotes(parser, buffer, is_name, ptr));
}

