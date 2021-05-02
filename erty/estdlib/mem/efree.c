/*
** EPITECH PROJECT, 2020
** LibErty
** File description:
** efree
*/

#include <stdlib.h>
#include "alloc.h"

static void efree_pointer(void *ptr, struct emalloc *list)
{
    for (; list; list = list->next)
        if (list->ptr == ptr) {
            free(list->ptr);
            list->free = true;
            list->ptr = NULL;
            return;

        }
    free_emalloc();
    efprintf(stderr, "Invalid free of %p nothing"
            " was found in the linked list\n", ptr);
    exit(255);
}

void efree(void *ptr)
{
    struct emalloc_header **header = NULL;
    struct emalloc *list = NULL;

    if (ptr == NULL)
        return;
    header = emalloc_header();
    list = (*header)->list;
    if (list == NULL) {
        free_emalloc();
        efprintf(stderr, "No allocation were done with done emalloc "
                "Your pointer must be invalid or allocated"
                " with the original malloc\n");
        exit(255);
    }
    efree_pointer(ptr, list);
}
