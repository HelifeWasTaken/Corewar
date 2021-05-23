/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** bonus
*/

#ifndef STRUC_H
    #define STRUC_H

    #include <ncurses.h>
    #include "corewar/vm.h"

    void draw_map(virtual_machine_t *vm, int y);
    void starting_color(void);
    int get_color_player(int8_t player);
    int get_color_champion(int8_t player);
    void draw_champion(virtual_machine_t *vm, int y);
    void draw_hud(vm_t *vm);

    #define DEF_COL 2
    #define COL_MIN 50
    #define COL_MAX (COLS - 4)
    #define ROW_MIN 50
    #define ROW_HUD (LINES - 17)


#endif
