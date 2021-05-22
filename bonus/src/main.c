/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** main
*/


#include <curses.h>
#include <time.h>
#include "corewar/bonus.h"
#include "corewar/vm.h"
#include <bits/types/clock_t.h>

int main(int ac, char **av)
{
    virtual_machine_t vm = {0};
    stdscr = initscr();
    keypad(stdscr,  TRUE);
    clock_t start = clock();

    if (ac <= 1)
        return (84);
    if (vm_init(&vm, av + 1) == false)
        return (85);
    starting_color();
    while (42) {
        tick_procs(&vm);
        if (((double)start/ (double)CLOCKS_PER_SEC) > 1) {
            clear();
            printf("je suis la\n");
        }
        draw_map(&vm);
        find_champion(&vm);
        refresh();
    }
}
