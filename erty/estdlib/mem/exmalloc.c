/*
** EPITECH PROJECT, 2021
** exmalloc
** File description:
** malloc
*/

#include "alloc.h"

static void emalloc_fail(void)
{
    free_emalloc();
    efputs(stderr, "Allocation failed");
    exit(84);
}

void *exmalloc(size_t size)
{
    void *ptr = malloc(size);

    if (ptr == NULL)
        emalloc_fail();
    return (ptr);
}
