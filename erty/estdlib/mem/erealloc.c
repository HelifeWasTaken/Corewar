/*
** EPITECH PROJECT, 2020
** LibErty
** File description:
** erealloc
*/

#include <erty/string/ecstring.h>
#include "alloc.h"

static void *init_ereallocation(size_t size, struct emalloc *list)
{
    void *tmp = NULL;

    if (size < list->size) {
        efputs(stderr, "You are trying to reallocate a "
                "pointer less than it's original size");
        free_emalloc();
        exit(84);
    }
    tmp = malloc(size);
    if (tmp == NULL) {
        efputs(stderr, "Could not allocate memory erealloc\n");
        free_emalloc();
        exit(84);
    }
    ememcpy(tmp, list->ptr, list->size);
    free(list->ptr);
    list->ptr = tmp;
    list->size = size;
    return (tmp);
}

void *erealloc(void *ptr, size_t size)
{
    struct emalloc_header **header = emalloc_header();
    struct emalloc *list = (*header)->list;

    if (ptr == NULL)
        return (emalloc(size));
    if (list == NULL) {
        efputs(stderr, "Trying to reallocate on a null list"
                " and not null pointer\n");
        free_emalloc();
        exit(84);
    }
    for (; list; list = list->next)
        if (ptr == list->ptr)
            break;
    if (list == NULL) {
        efprintf(stderr, "Invalid reallocation of %p\n", ptr);
        free_emalloc();
        exit(84);
    }
    return (init_ereallocation(size, list));
}
