/*
** EPITECH PROJECT, 2021
** opts
** File description:
** opts
*/

#include <corewar/vm.h>

static int check_invalid_args_opt_champion(char ***av, size_t i, int ret[3])
{
    if (estrcmp((*av)[i], "-n") != 0 && estrcmp((*av)[i], "-a") != 0 &&
            estrcmp((*av)[i], "-dump") != 0 && ret[0] != 0 && ret[1] != 0) {
        efprintf(stderr, "Invalid argument found: %s\n", (*av)[i]);
        return (2);
    }
    if (estrcmp((*av)[i], "-dump") == 0) {
        i += 2;
        if ((*av)[i] == NULL) {
            *av += 2;
            return (1);
        }
    }
    return (0);
}

static bool end_get_opt_champion(char ***av, size_t i,
        uint32_t *champion_index, char ***champion_tab)
{
    if ((*av)[i] == NULL) {
        efprintf(stderr, "Found parameters but no champion\n");
        return (false);
    }
    eappend_tab(champion_tab, (*av)[i]);
    if (i)
        *av += i;
    else
        *av += 1;
    (*champion_index)++;
    return (true);
}


bool get_opt_champion(vm_t *vm, char ***champion_tab,
        uint32_t *champion_index, char ***av)
{
    size_t i = 0;
    int ret[3] = {0};

    while ((*av)[i] && (*av)[i][0] == '-') {
        if ((ret[0] = load_number_arg(*av,
                    &vm->champion[*champion_index].prog_number, &i, "-n")) == 2)
            return (false);
        if ((ret[1] = load_number_arg(*av,
                    &vm->champion[*champion_index].pc.addr, &i, "-a")) == 2)
            return (false);
        if ((ret[2] = check_invalid_args_opt_champion(av, i, ret)) == 2)
            return (false);
        if (ret[2] == 1)
            return (true);
    }
    return (end_get_opt_champion(av, i, champion_index, champion_tab));
}
