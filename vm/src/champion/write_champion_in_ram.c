/*
** EPITECH PROJECT, 2021
** write
** File description:
** in ram
*/

#include "champion_loader.h"

static bool try_best_fit_for_champion(struct virtual_machine *vm,
        struct champion_loader *loader)
{
    if (vm->champion[loader->i].header.prog_size > (MEM_SIZE / loader->count))
        return (false);
    vm->champion[loader->i].pc.addr = (MEM_SIZE / loader->count) * loader->i;
    return (true);
}

static bool get_fit_for_champion_in_ram(struct virtual_machine *vm,
        struct champion_loader *loader)
{
    if (try_best_fit_for_champion(vm, loader) == true)
        return (true);
    efprintf(stderr, "Could not fit champion n°%d (%s) in ram\n", loader->i + 1,
            vm->champion[loader->i].header.prog_name);
    return (false);
}

bool vm_write_champion_in_ram(struct virtual_machine *vm,
        struct champion_loader *loader)
{
    size_t readed = 0;
    ssize_t ret = -1;
    char buf = 0;

    if (get_fit_for_champion_in_ram(vm, loader) == false)
        return (false);
    do {
        if ((ret = read(loader->fd, &buf, 1)) == -1) {
            efprintf(stderr, "Read failed\n");
            return (false);
        }
        vm->memory[(vm->champion[loader->i].pc.addr +
                readed) % MEM_SIZE].byte = buf;
        vm->memory[(vm->champion[loader->i].pc.addr +
                readed) % MEM_SIZE].player = loader->i;
        readed += ret;
    } while (ret > 0 && readed != vm->champion[loader->i].header.prog_size);
    add_proc_front(&vm->proc, &(struct proc){ .player = loader->i,
            .pc = vm->champion[loader->i].pc });
    return (readed == vm->champion[loader->i].header.prog_size);
}
