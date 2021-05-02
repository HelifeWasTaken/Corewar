/*
** EPITECH PROJECT, 2021
** egetline
** File description:
** erty
*/

#ifndef __ERTY_EGETLINE__
    #define __ERTY_EGETLINE__

    #include <unistd.h>
    #include <stddef.h>
    #include <fcntl.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <erty/estdlib.h>

    #define GETLINE_BUF_SIZE        (4096 * 2)

    ssize_t my_getline(char **res, int fd);

#endif
