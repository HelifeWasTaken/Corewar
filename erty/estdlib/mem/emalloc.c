/*
** EPITECH PROJECT, 2020
** LibErty
** File description:
** emalloc
*/

#include <stdlib.h>
#include <erty/estdio.h>

static const char *ERR_ALLOC_MSG = "Fatal error the impossible happened"
    " You do not have any memory left! Aborting safely...";

void *emalloc(size_t size)
{
    void *ptr = malloc(size);

    if (ptr == NULL) {
        efputs(stderr, ERR_ALLOC_MSG);
        exit(84);
    }
    return (ptr);
}
