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
    unsigned int count = ecount_tab(champion_files);

    for (unsigned int i = 0; i < count; i++) {
        if (vm_champion_init(vm, champion_files[i], i, count) == false)
            return (false);
        vm->champion_count++;
    }
    return (true);
}
