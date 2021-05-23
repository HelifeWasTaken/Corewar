/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** draw
*/

#include "corewar/bonus.h"
#include <curses.h>


static const char *WINDOWS_LOGO[] = {
    "=======================================================",
    "||                                                   ||",
    "||   _       _--\"\"--_                                ||",
    "||     \" --\"\"   |    |   .--.           |    ||      ||",
    "||   \" .  |     |    |  |    |          |    ||      ||",
    "||   _    |  _--\"\"--_|  |----| |.-  .-  |.-. ||      ||",
    "||     \" --\"\"   |    |  |    | |   |  | |  |         ||",
    "||   \" . _|     |    |  |    | |     -( |  |         ||",
    "||   _    |  _--\"\"--_|             |  |              ||",
    "||     \" --\"\"                       --               ||",
    "||                                                   ||",
    "=======================================================",
    NULL
};


void draw_hud(vm_t *vm)
{
    int y = ROW_HUD + 4;

    move(ROW_HUD + 1, 0);
    attron(COLOR_PAIR(10));
    printw("Last Live: [%d], Live count: [%d], Cycle to die: [%d],"
            " Champion count: [%d]\n",
        vm->last_live, vm->live_count, vm->cycle_to_die, vm->champion_count);
    for (unsigned int i = 0; i < vm->champion_count; i++)
        printw("%s[ Player: [%d], Name: [%s] ]", i ? "   " : "",
            i, vm->champion[i].header.prog_name);
    for (unsigned int i = 0; WINDOWS_LOGO[i]; i++)
        mvprintw(y++, COLS / 2 - 27, "%s", WINDOWS_LOGO[i]);
}

static void draw_champion_internal(proc_t *proc, int y)
{
    int col = DEF_COL;
    int lign = 0;
    int i = y * COLS;

    if (i > proc->pc.addr)
        return;
    for (; i != proc->pc.addr && lign + 2 < ROW_HUD; i++) {
        attron(COLOR_PAIR(get_color_champion(proc->player)));
        col += 2;
        if (2 + col >= COL_MAX) {
            col = DEF_COL;
            lign += 2;
        }
    }
    if (i == proc->pc.addr)
        mvprintw(lign, col, "X");
}

void draw_champion(virtual_machine_t *vm, int y)
{
    for (proc_t *proc = vm->proc; proc != NULL; proc = proc->next) {
        draw_champion_internal(proc, y);
    }
}

void draw_map(virtual_machine_t *vm, int y)
{
    int col = DEF_COL;
    int lign = 0;
    int i = COLS * y;

    attron(COLOR_PAIR(10));
    for (; i < MEM_SIZE && lign + 1 < ROW_HUD; i++) {
        attron(COLOR_PAIR(get_color_player(vm->memory[i].player)));
        mvprintw(lign, col, " ");
        col += 2;
        if (2 + col >= COL_MAX) {
            attron(COLOR_PAIR(10));
            col = DEF_COL;
            lign += 2;
        }
    }
}
