/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#include <corewar/asm.h>
#include <erty/estdio.h>
#include <erty/eendian.h>

int compiler(parser_t *parser, char const *filename)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        efprintf(stderr, "Could not generate binary file\n");
        return (84);
    }
    compiler_internal(parser, fd);
    close(fd);
    return (0);
}

int assembler(char const *filename, int fd)
{
    parser_t parser = {0};
    size_t filename_size = estrlen(filename);
    char buf[filename_size + 5];

    ememset(buf, 0, filename_size + 5);
    ememcpy(buf, filename, filename_size);
    if (read_header(&parser, fd) == false)
        return (84);
    if (pre_parsing(&parser, fd) == false)
        return (84);
    if (label_replacement(&parser) == false)
        return (84);
    estrcpy(buf + filename_size - (eendswith(filename, ".s") ? 2 : 0), ".cor");
    return (compiler(&parser, buf));
}

int main(int ac, char **av)
{
    int ret = 0;
    int fd = 0;

    if (ac != 2) {
        efprintf(stderr, "%s\n", USAGE);
        return (84);
    }
    if ((fd = open_file(av[1])) == -1)
        return (84);
    ret = assembler(av[1], fd);
    free_emalloc();
    return (ret);
}
