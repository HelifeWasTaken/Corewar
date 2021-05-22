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

    void draw_map(virtual_machine_t *vm);
    void starting_color(void);
    int get_color_player(int8_t player);
    int get_color_champion(int8_t player);
    void find_champion(virtual_machine_t *vm);

#endif
