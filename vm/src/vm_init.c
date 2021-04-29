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
    for (unsigned int i = 0; champion_files[i]; i++)
        if (i >= 4) {
            efprintf(stderr, "Champion count is too high\n");
            return (false);
        }
    ememset(vm, 0, sizeof(struct virtual_machine));
    for (unsigned int i = 0; champion_files[i]; i++)
        if (vm_champion_init(&vm->champion[i], champion_files[i]) == false)
            return (false);
    return (true);
}
