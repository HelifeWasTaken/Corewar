/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** draw
*/

#include "corewar/bonus.h"

void draw_map(virtual_machine_t *vm, int y)
{
    int col = 0;
    int lign = 0;

    for (int i = COLS * y; i < MEM_SIZE; i++) {
        attron(COLOR_PAIR(get_color_player(vm->memory[i].player)));
        mvprintw((2 + lign), 3 + (col * 3), "%02x", vm->memory[i].byte);
        col++;
        if (3 + (col * 3) >= COLS - 3) {
            col = 0;
            lign++;
        }
    }
}

