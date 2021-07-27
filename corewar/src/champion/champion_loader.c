/*
** EPITECH PROJECT, 2021
** read
** File description:
** header
*/

#include "champion_loader.h"

static bool vm_champion_header_reader(struct champion *champion,
        struct champion_loader *loader)
{
    if (read_memory_byte(loader->fd, &champion->header,
                sizeof(struct header_s)) == false) {
        efprintf(stderr, "%s: Header has an invalid checksum\n", loader->file);
        return (false);
    }
    champion->header.magic = u32_swap_endian(champion->header.magic);
    champion->header.prog_size = u32_swap_endian(champion->header.prog_size);
    champion->header.comment[COMMENT_LENGTH] = 0;
    champion->header.prog_name[PROG_NAME_LENGTH] = 0;
    if (champion->header.magic != MAGIC_NUMBER) {
        efprintf(stderr, "%s: Header has an invalid checksum\n", loader->file);
        return (false);
    }
    return (true);
}

bool vm_champion_init(struct virtual_machine *vm, char const *file,
        const unsigned int i, unsigned int count)
{
    struct champion_loader loader = { -1, i, count, file};

    if (check_champion_stat_and_open(&loader) == false)
        return (false);
    if (vm_champion_header_reader(&vm->champion[i], &loader) == false) {
        close(loader.fd);
        return (false);
    }
    if (vm_write_champion_in_ram(vm, &loader) == false) {
        close(loader.fd);
        return (false);
    }
    close(loader.fd);
    return (true);
}
