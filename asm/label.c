/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** asm
*/

#include <corewar/asm.h>
#include <stdlib.h>

static struct label *label_node(struct label *data)
{
    struct label *new = ecalloc(sizeof(struct label), 1);

    new->name = data->name;
    new->index = data->index;
    return (new);
}

static void label_push_front(struct label **head, struct label *data)
{
    struct label *ptr = *head;

    if (*head == NULL) {
        *head = label_node(data);
        return;
    }
    for (; ptr->next; ptr = ptr->next) {
        if (estrcmp(ptr->name, data->name) == 0) {
            efprintf(stderr, "Multiple reference of label: [%s] found\n",
                    data->name);
            free_emalloc();
            exit(84);
        }
    }
    ptr->next = label_node(data);
}

struct label *get_label(struct label *head, char *search)
{
    for (; head; head = head->next)
        if (estrcmp(head->name, search) == 0)
            return (head);
    return (NULL);
}

static bool parse_label_process(char *buffer,
        char *buffer_offset, parser_t *parser, size_t i)
{
    struct label tmp = {0};

    if (buffer_offset - buffer == 1) {
        efprintf(stderr, "Missing name for label in line: %d", parser->line);
        return (false);
    }
    for (; i < (size_t)(buffer_offset - buffer); i++)
        if (istoken(buffer[i], LABEL_CHARS) == false) {
            efprintf(stderr, "Invalid character in label at: %d:%d\n",
                    parser->line, i);
            return (false);
        }
    tmp.name = estrndup(buffer + parser->col, i - parser->col);
    tmp.index = parser->mem_index;
    label_push_front(&parser->label, &tmp);
    parser->col = i + 2;
    return (true);
}

bool parse_label(parser_t *parser, char *buffer)
{
    skip_spaces(parser, buffer);
    for (size_t i = parser->col; buffer[i] && !istoken(buffer[i], " \t"); i++)
        if (buffer[i] == ':')
            return (parse_label_process(buffer, buffer + i, parser, i));
    return (true);
}
