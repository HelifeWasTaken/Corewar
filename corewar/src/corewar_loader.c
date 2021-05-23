/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** core
*/

#include <corewar/vm.h>

static void reset_vm(vm_t *vm)
{
    ememset(vm, 0, sizeof(struct virtual_machine));
    vm->last_instance = 1;
    vm->last_live = -1;
    vm->live_count = 0;
    vm->cycle_to_die = CYCLE_TO_DIE;
    vm->dump = -1;
    for (uint8_t i = 0; i < 4; i++) {
        vm->champion[i].pc.addr = -1;
        vm->champion[i].pc.next_addr = -1;
        vm->champion[i].prog_number = -1;
    }
    for (unsigned int i = 0; i < MEM_SIZE; i++)
        vm->memory[i].player = NOT_A_PLAYER;
}

static int load_vm(virtual_machine_t *vm, char **argv, char ***champion_tab)
{
    if (get_opt(argv, vm, champion_tab) == false) {
        return (84);
    }
    if (*champion_tab == NULL || ecount_tab(*champion_tab) == 1) {
        efprintf(stderr, "Too few champions were provided\n");
        return (84);
    }
    return (0);
}

int core_loader(vm_t *vm, char **argv, int argc)
{
    char **champion_tab = NULL;

    reset_vm(vm);
    if (argc <= 1)
        return (84);
    if (load_vm(vm, argv + 1, &champion_tab) == 84) {
        free_emalloc();
        return (84);
    }
    if (vm_init(vm, champion_tab) == false) {
        free_emalloc();
        return (84);
    }
    free_esplit(champion_tab);
    return (0);
}
