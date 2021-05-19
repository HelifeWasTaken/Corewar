/*
** EPITECH PROJECT, 2020
** LibErty
** File description:
** emalloc
*/

#include <stdlib.h>
#include <erty/estdio.h>
#include "alloc.h"

static struct emalloc *create_emalloc_node(void *ptr, size_t size)
{
    struct emalloc *new = exmalloc(sizeof(struct emalloc));

    new->ptr = ptr;
    new->size = size;
    new->free = false;
    new->next = NULL;
    return (new);
}

static void insert_emalloc(void *ptr, size_t size)
{
    struct emalloc_header **header = emalloc_header();
    struct emalloc *list = (*header)->list;

    if (list == NULL) {
        (*header)->list = create_emalloc_node(ptr, size);
        return;
    }
    for (; list->next; list = list->next)
        if (list->free == true) {
            list->ptr = ptr;
            list->size = size;
            list->free = false;
            return;
        }
    list->next = create_emalloc_node(ptr, size);
}

void *emalloc(size_t size)
{
    void *ptr = exmalloc(size);

    insert_emalloc(ptr, size);
    return (ptr);
}
