/*
** EPITECH PROJECT, 2021
** alloc
** File description:
** alloc
*/

#ifndef ERTY_EALLOC_H
    #define ERTY_EALLOC_H

    #include <stdlib.h>
    #include <stdbool.h>
    #include <erty/string/ecstring.h>
    #include <erty/eprintf.h>
    #include <erty/estdio.h>

    struct emalloc {
        void *ptr;
        bool free;
        size_t size;
        struct emalloc *next;
    };

    struct emalloc_header {
        struct emalloc *list;
    };

    struct emalloc_header **emalloc_header(void);
    void free_emalloc(void);
    void efree(void *ptr);
    void *ecalloc(size_t nmemb, size_t size);
    void *emalloc(size_t size);
    void *erealloc(void *ptr, size_t size);
    void *exmalloc(size_t size);

#endif
