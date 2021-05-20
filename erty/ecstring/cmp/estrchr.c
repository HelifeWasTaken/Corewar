/*
** EPITECH PROJECT, 2020
** LibErty
** File description:
** estrchr
*/

#include <erty/ectypes.h>

cstr_t estrchr(const_cstr_t str, i32_t c)
{
    for (size_t i = 0; str[i]; i++)
        if (str[i] == c)
            return ((char *)&str[i]);
    return (NULL);
}

cstr_t estrrchr(const_cstr_t str, i32_t c)
{
    char *ptr = estrchr(str, c);
    char *old = (char *)str;

    if (ptr == NULL)
        return (NULL);
    while (ptr != NULL) {
        old = ptr;
        ptr = estrchr(++ptr, c);
    }
    return (old);
}
