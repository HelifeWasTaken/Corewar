/*
** EPITECH PROJECT, 2021
** read
** File description:
** header
*/

#include <corewar/vm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <erty/estdlib.h>
#include <erty/eprintf.h>
#include <stdbool.h>

struct memory_reader_header {
    const char      *error;
    const size_t    offset;
    const size_t    size;
};

bool read_mem(const int fd, void *mem, const size_t size)
{
    ssize_t read_ret = -1;
    size_t read_size = 0;

    do {
        read_ret = read(fd, mem, size);
        read_size += read_ret;
    } while (read_ret > 0);
    return (read_ret != -1 && read_size == size);
}

static const struct memory_reader_header MEM_READER_HEADER[] = {
    {
        .error  = "Error reading the magic checksum of ",
        .offset = offsetof(struct header_s, magic),
        .size   = sizeof(int)
    },
    {
        .error  = "Error reading the program name of ",
        .offset = offsetof(struct header_s, prog_name),
        .size   = sizeof(char) * PROG_NAME_LENGTH
    },
    {
        .error  = "Error reading the program size of ",
        .offset = offsetof(struct header_s, prog_size),
        .size   = sizeof(int)
    },
    {
        .error  = "Error reading the program comment of ",
        .offset = offsetof(struct header_s, comment),
        .size   = sizeof(char) * COMMENT_LENGTH
    }
};

static bool vm_champion_header_reader(struct champion *champion,
        char const *file)
{
    char *ptr = NULL;

    for (usize_t i = 0; i < ARRAY_SIZE(MEM_READER_HEADER); i++) {
        ptr = (BYTE *)&champion->header + MEM_READER_HEADER[i].offset;
        if (read_mem(champion->fd, ptr, MEM_READER_HEADER[i].size) == false) {
            efprintf(stderr, "%s%s\n", MEM_READER_HEADER[i].error, file);
            return (false);
        }
    }
    champion->header.comment[COMMENT_LENGTH] = 0;
    champion->header.prog_name[PROG_NAME_LENGTH] = 0;
    return (true);
}

static bool check_champion_stat_and_open(struct champion *champion,
        struct stat *st, char const *file)
{
    if (stat(file, st) == -1) {
        efprintf(stderr, "%s: Stat failed\n", file);
        return (false);
    }
    if (st->st_size < HEADER_SIZE) {
        efprintf(stderr, "%s: Has an invalid header\n", file);
        return (false);
    }
    champion->fd = open(file, O_RDONLY);
    if (champion->fd == -1) {
        efprintf(stderr, "%s: Bad file descrpitor\n", file);
        return (false);
    }
    return (true);
}

bool vm_champion_init(struct champion *champion, char const *file)
{
    struct stat st = {0};

    *champion = DEFAULT_CHAMPION;
    if (check_champion_stat_and_open(champion, &st, file) == false)
        return (false);
    if (vm_champion_header_reader(champion, file) == false) {
        close(champion->fd);
        return (false);
    }
    return (true);
}
