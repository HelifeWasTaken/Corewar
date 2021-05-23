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

static void dump_memory(struct memory *mem)
{
    int col = 0;

    eprintf("====== START ======\n");
    eprintf("\n0x%02x == ", 0);
    for (int i = 0; i < MEM_SIZE; i++) {
        eprintf("[%02x]", mem[i].byte);
        if (++col >= 40)
            eprintf("\n0x%02x == ", i);
    }
    eprintf("======= END ======\n");
}

int main(int argc UNUSED, char *argv[] UNUSED)
{
    struct virtual_machine vm = {0};

    if (core_loader(&vm, argv, argc) == 84)
        return (84);
    stdscr = initscr();
    keypad(stdscr,  TRUE);
    nodelay(stdscr, true);
    starting_color();
    corewar(&vm);
    return (EXIT_SUCCESS);
}
