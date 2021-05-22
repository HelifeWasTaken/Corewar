/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** update
*/

#include "corewar/bonus.h"
#include "corewar/op.h"
#include "corewar/vm.h"
#include <curses.h>

int get_color_player(int8_t player)
{
    switch (player) {
        case 0:
            return (1);
        case 1:
            return (2);
        case 2:
            return (3);
        case 3:
            return (4);
    }
    return (5);
}

int get_color_champion(int8_t player)
{
    switch (player) {
        case 0:
            return (6);
        case 1:
            return (7);
        case 2:
            return (8);
        case 3:
            return (9);
    }
    return (5);
}

void find_champion(virtual_machine_t *vm)
{
    for (proc_t *proc = vm->proc; proc != NULL; proc = proc->next) {
        attron(COLOR_PAIR(get_color_champion(proc->player)));
        mvprintw((proc->pc.addr % 64) + 2, (proc->pc.addr / 64) * 3 + 3, "XX");
    }
}

void starting_color(void)
{
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_BLUE);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(4, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, 8);
    init_pair(6, COLOR_BLACK, 9);
    init_pair(7, COLOR_BLACK, 12);
    init_pair(8, COLOR_BLACK, 11);
    init_pair(9, COLOR_BLACK, 13);
}
