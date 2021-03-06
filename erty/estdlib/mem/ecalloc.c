/*
** EPITECH PROJECT, 2020
** LibErty
** File description:
** ecalloc
*/

#include <erty/string/ecstring.h>
#include "alloc.h"

void *ecalloc(size_t nmemb, size_t size)
{
    void *ptr = emalloc(nmemb * size);

    ememset(ptr, 0, nmemb * size);
    return (ptr);
}
