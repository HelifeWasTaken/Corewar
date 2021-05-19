/*
** EPITECH PROJECT, 2021
** emalloc
** File description:
** header
*/

#include "alloc.h"

struct emalloc_header **emalloc_header(void)
{
    static struct emalloc_header *header = NULL;

    if (header == NULL) {
        header = malloc(sizeof(struct emalloc_header));
        if (header != NULL) {
            ememset(header, 0, sizeof(struct emalloc_header));
            return (&header);
        }
        efputs(stderr, "Could not allocate for header Emalloc");
        exit(84);
    }
    return (&header);
}

static void free_emalloc_r(struct emalloc **list)
{
    if (*list == NULL)
        return;
    free_emalloc_r(&(*list)->next);
    if ((*list)->free == false)
        free((*list)->ptr);
    (*list)->ptr = NULL;
    (*list)->free = true;
    free(*list);
}

void free_emalloc(void)
{
    struct emalloc_header **header = emalloc_header();

    if ((*header)->list != NULL)
        free_emalloc_r(&(*header)->list);
    free(*header);
    *header = NULL;
}
