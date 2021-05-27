/*
** EPITECH PROJECT, 2021
** write
** File description:
** in ram
*/

#include "champion_loader.h"

static int get_free_id_for_champion(struct virtual_machine *vm)
{
    int param[4] = {0};

    for (int i = 0; i < 4; i++)
        if (vm->champion[i].prog_number != -1)
            param[vm->champion[i].prog_number - 1] = 1;
    for (int i = 0; i < 4; i++)
        if (param[i] == 0)
            return (i + 1);
    efprintf(stderr, "You should not be there\n");
    return (0);
}

static bool try_best_fit_for_champion(struct virtual_machine *vm,
        struct champion_loader *loader)
{
    if (vm->champion[loader->i].header.prog_size > (MEM_SIZE / loader->count))
        return (false);
    if (vm->champion[loader->i].prog_number == -1)
        vm->champion[loader->i].prog_number = get_free_id_for_champion(vm);
    vm->champion[loader->i].pc.addr =
        (MEM_SIZE / loader->count) * (vm->champion[loader->i].prog_number - 1);
    return (true);
}

static bool get_fit_for_champion_in_ram(struct virtual_machine *vm,
        struct champion_loader *loader)
{
    unsigned int count = 0;

    if (try_best_fit_for_champion(vm, loader) == false) {
        efprintf(stderr, "Could not fit champion n°%d (%s) in ram"
                "(Prog Too big)\n",
                vm->champion[loader->i].prog_number,
                vm->champion[loader->i].header.prog_name);
        return (false);
    }
    for (unsigned int i = vm->champion[loader->i].pc.addr;
            count < vm->champion[loader->i].header.prog_size; i++) {
        if (vm->memory[i % MEM_SIZE].player != -1) {
            efprintf(stderr, "Could not fit champion n°%d (%s) in ram (Addr)\n",
                    vm->champion[loader->i].prog_number,
                    vm->champion[loader->i].header.prog_name);
            return (false);
        }
        count++;
    }
    return (true);
}

static bool vm_write_champion_in_ram_process(struct virtual_machine *vm UNUSED,
        struct champion_loader *loader, size_t *readed, ssize_t *ret)
{
    char buf = 0;

    if ((*ret = read(loader->fd, &buf, 1)) == -1) {
        efprintf(stderr, "Read failed\n");
        return (false);
    }
    vm->memory[(vm->champion[loader->i].pc.addr +
            *readed) % MEM_SIZE].byte = buf;
    vm->memory[(vm->champion[loader->i].pc.addr + *readed) % MEM_SIZE].player =
        vm->champion[loader->i].prog_number - 1;
    *readed += *ret;
    return (true);
}

bool vm_write_champion_in_ram(struct virtual_machine *vm,
        struct champion_loader *loader)
{
    size_t readed = 0;
    ssize_t ret = -1;

    if (get_fit_for_champion_in_ram(vm, loader) == false)
        return (false);
    do {
        if (!vm_write_champion_in_ram_process(vm, loader, &readed, &ret))
            return (false);
    } while (ret > 0 && readed != vm->champion[loader->i].header.prog_size);
    add_proc_back(&vm->proc, &(struct proc){
            .player = vm->champion[loader->i].prog_number - 1,
            .pc = vm->champion[loader->i].pc }, &vm->last_instance);
    return (readed == vm->champion[loader->i].header.prog_size);
}
