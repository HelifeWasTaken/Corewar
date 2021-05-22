/*
** EPITECH PROJECT, 2021
** vm_init
** File description:
** vm
*/

#include <corewar/vm.h>
#include <erty/string/ecstring.h>
#include <erty/eprintf.h>

bool vm_init(struct virtual_machine *vm, char **champion_files)
{
    size_t count = ecount_tab(champion_files);

    for (unsigned int i = 0; champion_files[i]; i++)
        if (i >= 4) {
            efprintf(stderr, "Champion count is too high\n");
            return (false);
        }
    ememset(vm, 0, sizeof(struct virtual_machine));
    vm->last_instance = 1;
    vm->last_live = -1;
    vm->live_count = 0;
    vm->cycle_to_die = CYCLE_TO_DIE;
    for (unsigned int i = 0; i < MEM_SIZE; i++)
        vm->memory[i].player = NOT_A_PLAYER;
    for (unsigned int i = 0; i < count; i++)
        if (vm_champion_init(vm, champion_files[i], i, count) == false)
            return (false);
    return (true);
}
