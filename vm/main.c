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
#include <ncurses.h>

/*
void init_colors(void)
{
    start_color();
    init_pair(0xff, COLOR_WHITE,    COLOR_BLACK);
    init_pair(1,    COLOR_RED,      COLOR_BLACK);
    init_pair(2,    COLOR_GREEN,    COLOR_BLACK);
    init_pair(3,    COLOR_BLUE,     COLOR_BLACK);
    init_pair(4,    COLOR_YELLOW,   COLOR_BLACK);
}

void draw_player_info(struct virtual_machine *vm)
{
    attron(COLOR_PAIR(0xff));
    for (int i = 0; i < CHAMPION_COUNT_MAX &&
            vm->champion[i].live != DEAD; i++) {
        attron(COLOR_PAIR(i + 1));
        printw("Player n°%d: [ magic: [0x%x] | prog_name: [%s] | "
                "prog_size: [%d] | comment: [%s] | Pc: [%d] ]\n",
                i + 1, vm->champion[i].header.magic,
                vm->champion[i].header.prog_name,
                vm->champion[i].header.prog_size,
                vm->champion[i].header.comment,
                vm->champion[i].pc.addr);
    }
    printw("\n\n\n");
}

void draw_machine_state(struct virtual_machine *vm)
{
    for (unsigned int i = 0; i < MEM_SIZE; i++) {
        if (vm->memory[i].player != -1)
            attron(COLOR_PAIR(vm->memory[i].player + 1));
        else
            attron(COLOR_PAIR(0xff));
        printw("[%02x]", vm->memory[i].byte);
        if ((i + 1) % 75 == 0)
            printw("\n");
    }
}

int main(int ac UNUSED, char **av UNUSED)
{
    struct virtual_machine vm = {0};

    if (ac == 1)
        return (84);
    if (vm_init(&vm, av + 1) == false)
        return (false);
    noecho();
    initscr();
    init_colors();
    draw_player_info(&vm);
    draw_machine_state(&vm);
    refresh();
    getch();
    endwin();
    return (0);
}
*/
int main(int argc UNUSED, char const *argv[] UNUSED)
{
    return 0;
}
