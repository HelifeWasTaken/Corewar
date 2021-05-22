/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** main
*/


#include <ncurses.h>
#include "corewar/vm.h"

static void    draw_map(t_vm *v, t_win w)
{
    int            i;
    int            col;
    int            row;
    int            color;

    i = 0;
    col = 0;
    row = 0;
    color = 7;
    while (i < MEM_SIZE)
    {
        color_picker(v, g_memory_mark, &i, &color);
        wattron(w.game, COLOR_PAIR(color));
        mvwprintw(w.game, (2 + row), 3 + (col * 3), "%02x", g_memory[i]);
        col++;
        i++;
        if (col == 64)
        {
            col = 0;
            row++;
        }
    }
    wattroff(w.game, COLOR_PAIR(7));
}

int main(int ac, char **av)
{
    stdsrc = initscr();
    keypad(stdscr,  TRUE);

    while (42) {
        clear();
        draw_map();
        refresh();
    }
}
