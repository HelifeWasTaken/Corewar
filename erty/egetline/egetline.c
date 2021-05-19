/*
** EPITECH PROJECT, 2021
** egetline
** File description:
** getline
*/

#include <erty/egetline.h>

struct egetline_reader {
    char buf[GETLINE_BUF_SIZE];
    size_t readed;
    size_t buf_index;
};

static void write_buffer(char **res, struct egetline_reader *reader)
{
    *res = erealloc(*res, reader->buf_index + reader->readed + 1);
    ememcpy(*res + reader->readed, reader->buf, reader->buf_index);
    (*res)[reader->buf_index + reader->readed] = 0;
    reader->readed += reader->buf_index;
    ememset(reader->buf, 0, reader->buf_index);
    reader->buf_index = 0;
}

static ssize_t end_getline(char **res, struct egetline_reader *reader,
        ssize_t read_ret)
{
    if (read_ret == -1) {
        if (*res != NULL)
            efree(*res);
        return (-1);
    }
    if (reader->buf[reader->buf_index] == '\n')
        reader->buf[reader->buf_index] = 0;
    write_buffer(res, reader);
    return (read_ret + reader->readed);
}

ssize_t egetline(char **res, int fd)
{
    struct egetline_reader reader = {0};
    ssize_t read_ret = -1;

    if (*res != NULL) {
        efree(*res);
        *res = NULL;
    }
    while ((read_ret = read(fd, reader.buf + reader.buf_index, 1)) > 0) {
        if (*(reader.buf + reader.buf_index) == '\n')
            break;
        if (++reader.buf_index >= GETLINE_BUF_SIZE - 1)
            write_buffer(res, &reader);
    }
    return (end_getline(res, &reader, read_ret));
}
