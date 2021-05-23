/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** draw
*/

#include "corewar/bonus.h"
#include <curses.h>

void draw_hud(vm_t *vm)
{
    move(ROW_HUD + 1, 0);
    attron(COLOR_PAIR(10));
    printw("Last Live: [%d], Live count: [%d], Cycle to die: [%d],"
            " Champion count: [%d]\n",
        vm->last_live, vm->live_count, vm->cycle_to_die, vm->champion_count);
    for (unsigned int i = 0; i < vm->champion_count; i++)
        printw(" [ Player: [%d], Name: [%s] ]",
            i, vm->champion[i].header.prog_name);
    printw("\n%s", WINDOWS_LOGO);
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
        col++;
        if (3 + (col * 3) >= COL_MAX) {
            col = DEF_COL;
            lign += 2;
        }
    }
    if (i == proc->pc.addr)
        mvprintw((2 + lign), 3 + (col * 3), "XX");
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
    mvprintw(2, 0, "0x%04x", i);
    for (; i < MEM_SIZE && lign + 2 < ROW_HUD; i++) {
        attron(COLOR_PAIR(get_color_player(vm->memory[i].player)));
        mvprintw((2 + lign), 3 + (col * 3), "%02x", vm->memory[i].byte);
        col++;
        if (3 + (col * 3) >= COL_MAX) {
            attron(COLOR_PAIR(10));
            mvprintw((2 + lign), 0, "0x%02x", i);
            col = DEF_COL;
            lign += 2;
        }
    }
}

