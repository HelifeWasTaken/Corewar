/*
** EPITECH PROJECT, 2021
** open
** File description:
** file
*/

#include <corewar/asm.h>

int open_file(char const *file)
{
    int fd = open(file, O_RDONLY);

    if (fd == -1)
        efprintf(stderr, "Could not open: [%s]\n", file);
    return (fd);
}
