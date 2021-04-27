/*
** EPITECH PROJECT, 2020
** LibErty
** File description:
** eappend_buff
*/

#include <erty/ebuffer.h>

static ssize_t safe_append_buff_nbyte(ebuff_t **buff_info,
        cstr_t toadd, size_t n);

ssize_t eappend_buff_nbytes(ebuff_t **buff_info, cstr_t toadd, size_t n)
{
    cstr_t ptr = NULL;

    if (!(*buff_info))
        return (-1);
    if (n > (*buff_info)->buff_size && (*buff_info)->flush == true)
        return (safe_append_buff_nbyte(buff_info, toadd, n));
    if (n + (*buff_info)->used >= (*buff_info)->buff_size) {
        if ((*buff_info)->flush) {
            eflush_buff(buff_info);
            ereset_buff(buff_info);
        } else
            erealloc_buff(buff_info, n);
    }
    if (!(*buff_info)->buff)
        return (-1);
    ptr = (*buff_info)->buff;
    ememcpy((*buff_info)->buff + (*buff_info)->used, toadd, n);
    (*buff_info)->buff = ptr;
    (*buff_info)->used += n;
    return (0);
}

static ssize_t safe_append_buff_nbyte(ebuff_t **buff_info,
        cstr_t toadd, size_t n)
{
    size_t ntmp = 0;

    eflush_buff(buff_info);
    ereset_buff(buff_info);
    while (n - ntmp > (*buff_info)->buff_size) {
        ewrite((*buff_info)->fd, toadd + ntmp, (*buff_info)->buff_size);
        ntmp += (*buff_info)->buff_size;
    }
    return (eappend_buff_nbytes(buff_info, toadd + ntmp, n - ntmp));
}
