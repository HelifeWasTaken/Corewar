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

static int handle_input(int *y)
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
            return (1);
    }
    if (*y < 0 || *y * COLS > MEM_SIZE)
        *y = 0;
    return (0);
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
        if (handle_input(&y) == 1)
            break;
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

    if (music == NULL || core_loader(&vm, argv, argc) == 84)
        return (84);
    sfMusic_play(music);
    stdscr = initscr();
    noecho();
    curs_set(0);
    keypad(stdscr,  TRUE);
    nodelay(stdscr, true);
    starting_color();
    corewar(&vm);
    free_emalloc();
    sfMusic_destroy(music);
    endwin();
    refresh();
    return (EXIT_SUCCESS);
}
