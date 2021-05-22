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
#include <stdlib.h>

static void handle_input(int *y)
{
    int ch = getch();

    switch (ch) {
        case KEY_UP:
            (*y)--;
            break;
        case KEY_DOWN:
            (*y)++;
            break;
        case 113:
            free_emalloc();
            exit(0);
    }
    if (*y < 0)
        *y = 0;
}

static int loop(struct virtual_machine *vm)
{
    int y = 0;
    clock_t start = clock();

    while (42) {
        tick_procs(vm);
        if (((double)start/ (double)CLOCKS_PER_SEC) > 1) {
            clear();
            printf("je suis la\n");
        }
        handle_input(&y);
        draw_map(vm, y);
        find_champion(vm, y);
        refresh();
    }
    return (0);
}

int main(int ac, char **av)
{
    virtual_machine_t vm = {0};

    if (ac <= 1)
        return (84);
    if (vm_init(&vm, av + 1) == false)
        return (85);
    stdscr = initscr();
    keypad(stdscr,  TRUE);
    nodelay(stdscr, true);
    starting_color();
    loop(&vm);
    return (0);
}
