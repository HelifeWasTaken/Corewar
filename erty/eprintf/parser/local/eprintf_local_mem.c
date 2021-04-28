/*
** EPITECH PROJECT, 2021
** eprintf
** File description:
** localmem
*/

#include <erty/eprintf.h>

void eprintf_local_mem(ebuff_t **buff, va_list *ap, eprintf_mod_t *mod)
{
    ucstr_t s = get_ptr_arg(ap, mod->len);
    u64_t n = get_unsigned_arg(ap, mod->len);

    eappend_buff_nbytes(buff, (cstr_t)s, n);
}
