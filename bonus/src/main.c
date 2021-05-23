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
#include <SFML/Audio.h>

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

static int corewar(struct virtual_machine *vm)
{
    int y = 0;
    clock_t start = clock();

    vm->cycle_before_dump = vm->dump;
    while (42) {
        tick_procs(vm);
        if (((double)start/ (double)CLOCKS_PER_SEC) > 1) {
            clear();
        }
        if (vm->cycle_before_dump > 0) {
            vm->cycle_before_dump--;
            continue;
        } else
            vm->cycle_before_dump = vm->dump;
        handle_input(&y);
        draw_map(vm, y);
        draw_champion(vm, y);
        draw_hud(vm);
        refresh();
    }
    return (0);
}

int main(int argc UNUSED, char *argv[] UNUSED)
{
    struct virtual_machine vm = {0};
    sfMusic *music = sfMusic_createFromFile("music.ogg");

    if (music == NULL)
        return (84);
    if (core_loader(&vm, argv, argc) == 84)
        return (84);
    noecho();
    sfMusic_play(music);
    stdscr = initscr();
    keypad(stdscr,  TRUE);
    nodelay(stdscr, true);
    starting_color();
    corewar(&vm);
    return (EXIT_SUCCESS);
}
