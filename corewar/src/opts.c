/*
** EPITECH PROJECT, 2021
** static
** File description:
** opts
*/

#include <corewar/vm.h>
#include <erty/estdlib.h>

int load_number_arg(char **av, int32_t *res, size_t *i, char *arg)
{
    if (estrcmp(av[*i], arg) != 0)
        return (1);
    if (av[*i + 1] == NULL) {
        efprintf(stderr, "Missing argument for %s\n", arg);
        return (2);
    }
    if (*res != -1) {
        efprintf(stderr, "Multiple occurence of %s argument found\n", arg);
        return (2);
    }
    if (estr_isnum(av[*i + 1]) == false) {
        efprintf(stderr, "Invalid number provided for %s argument\n", arg);
        return (2);
    }
    *res = eatoi(av[*i + 1]).value;
    *i += 2;
    return (0);
}

static bool check_opts_arg_a(vm_t *vm)
{
    for (uint8_t i = 0; i < 4; i++) {
        if (vm->champion[i].pc.addr == -1)
            continue;
        if (vm->champion[i].pc.addr > MEM_SIZE || vm->champion[i].pc.addr < 0) {
            efprintf(stderr, "You specified a load address out of range: %d\n",
                    vm->champion[i].pc.addr);
            return (false);
        }
    }
    return (true);
}

static bool check_opts_arg_n(vm_t *vm)
{
    bool params[4] = {0};

    for (uint8_t i = 0; i < 4; i++) {
        if (vm->champion[i].prog_number == -1)
            continue;
        if (vm->champion[i].prog_number > 4 ||
                vm->champion[i].prog_number <= 0) {
            efprintf(stderr,
                    "Please specify a prog_number between 1 and 4\n", stderr);
            return (false);
        }
        if (params[vm->champion[i].prog_number - 1] != false) {
            efprintf(stderr, "You specified the prog number %d "
                    "for two champions\n", vm->champion[i].prog_number);
            return (false);
        }
    }
    return (true);
}

bool get_opt(char **argv, vm_t *vm, char ***champion_tab)
{
    size_t i = 0;

    for (; argv[i]; i++) {
        if (load_number_arg(argv, &vm->dump, &i, "-dump") == 2)
            return (false);
        if (argv[i] == NULL)
            break;
    }
    while (*argv) {
        if (get_opt_champion(vm, champion_tab,
                    &vm->champion_count, &argv) == false)
            return (false);
        if (vm->champion_count > 4) {
            efprintf(stderr, "Too many champions were provided\n");
            return (false);
        }
    }
    return (check_opts_arg_a(vm) && check_opts_arg_n(vm));
}
