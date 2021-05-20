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

char *get_output_filename(char const *filename)
{
    char *raw_filename = estrrchr(filename, '/');
    char *file = NULL;

    if (raw_filename == NULL)
        raw_filename = (char *)filename;
    if (*raw_filename == '/')
        raw_filename++;
    if (eendswith(raw_filename, ".s") == true) {
        file = emalloc(sizeof(char) * (estrlen(raw_filename) + 3));
        estrcpy(file, raw_filename);
        estrcpy(file + estrlen(raw_filename) - 2, ".cor");
        return (file);
    }
    file = emalloc(sizeof(char) * (estrlen(raw_filename) + 5));
    estrcpy(file, raw_filename);
    estrcpy(file + estrlen(raw_filename), ".cor");
    return (file);
}

int assembler(char const *filename, int fd)
{
    parser_t parser = {0};

    if (read_header(&parser, fd) == false)
        return (84);
    if (pre_parsing(&parser, fd) == false)
        return (84);
    if (label_replacement(&parser) == false)
        return (84);
    return (compiler(&parser, get_output_filename(filename)));
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
