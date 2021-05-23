/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#include <erty/getopt.h>
#include <erty/ecolors.h>
#include <erty/string/esstring.h>
#include <stdlib.h>
#include <corewar/vm.h>
#include <stdlib.h>

static void chose_color(int color)
{
    switch (color) {
        case -1:
            eprintf("%s", WHITE);
            break;
        case 0:
            eprintf("%s", RED);
            break;
        case 1:
            eprintf("%s", GREEN);
            break;
        case 2:
            eprintf("%s", YELLOW);
            break;
        case 3:
            eprintf("%s", PURPLE);
            break;
    }
}

static void dump_memory(struct memory *mem)
{
    int col = 0;

    chose_color(-1);
    eprintf("====== START ======\n");
    eprintf("\n0x%04x == ", 0);
    for (int i = 0; i < MEM_SIZE; i++) {
        chose_color(mem[i].player);
        eprintf("[%02x]", mem[i].byte);
        if (++col >= 40) {
            chose_color(-1);
            eprintf("\n0x%04x == ", i);
            col = 0;
        }
    }
    eprintf("\n======= END ======\n");
}

static void corewar(vm_t *vm)
{
    vm->cycle_before_dump = 0;
    while (1) {
        tick_procs(vm);
        if (vm->cycle_before_dump > 0) {
            vm->cycle_before_dump--;
        } else if (vm->cycle_before_dump != -1) {
            vm->cycle_before_dump = vm->dump;
            dump_memory(vm->memory);
        }
    }
}

int main(int argc UNUSED, char *argv[] UNUSED)
{
    struct virtual_machine vm;

    ememset(&vm, 0, sizeof(struct virtual_machine));
    if (core_loader(&vm, argv, argc) == 84)
        return (84);
    corewar(&vm);
    return (EXIT_SUCCESS);
}
