/*
** EPITECH PROJECT, 2020
** LibErty
** File description:
** eappend_buff
*/

#include <erty/ebuffer.h>

ssize_t eappend_buff_str(ebuff_t **buff_info, cstr_t toadd)
{
    return (eappend_buff_nbytes(buff_info, toadd, estrlen(toadd)));
}

ssize_t eappend_buff_char(ebuff_t **buff_info, i32_t c)
{
    return (eappend_buff_nbytes(buff_info, (cstr_t)&c, 1));
}

ssize_t eappend_buff_unsigned_number(ebuff_t **buff,
        u64_t nb, char const *base, u8_t base_size)
{
    return ((nb >= base_size) ?
            eappend_buff_unsigned_number(
                buff, nb / base_size, base, base_size) +
            eappend_buff_char(buff, base[nb % base_size]) :
            eappend_buff_char(buff, base[nb]));
}

ssize_t eappend_buff_signed_number(ebuff_t **buff,
        i64_t nb, char const *base, u8_t base_size)
{
    return ((nb >= 0) ?
            eappend_buff_unsigned_number(buff, nb, base, base_size) :
            eappend_buff_char(buff, '-') +
            eappend_buff_unsigned_number(buff, -nb, base, base_size));
}
