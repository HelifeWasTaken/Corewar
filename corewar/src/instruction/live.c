/*
** EPITECH PROJECT, 2021
** live
** File description:
** live
*/

#ifndef GRAPHIC
#include <corewar/vm.h>
#else
#include <corewar/bonus.h>
#endif
#include <stdlib.h>

static void make_one_player_win(vm_t *vm)
{
    int player_last_living = 0;

#ifdef GRAPHIC
    clear();
    endwin();
#endif
    for (; player_last_living < 2; player_last_living++)
        if (vm->champion[player_last_living].prog_number == vm->last_live + 1)
            break;
    eprintf("The player %d (%s) has won\n", vm->last_live + 1,
            vm->champion[player_last_living].header.prog_name);
    free_emalloc();
    exit(0);
}

static void death_sentence_process(proc_t **prev, proc_t **current,
        proc_t **next)
{
    if ((*current)->live == false) {
        (*prev)->next = *next;
    } else {
        *prev = *current;
        (*current)->live = false;
    }
}

static void death_sentence(vm_t *vm)
{
    proc_t *prev = NULL;
    proc_t *current = vm->proc;
    proc_t *next = NULL;
    int alive[4] = {0};

    while (vm->proc) {
        current = vm->proc;
        if (vm->proc->live == true)
            break;
        vm->proc = vm->proc->next;
    }
    while (current) {
        next = current->next;
        if (current->live)
            alive[current->player] = 1;
        death_sentence_process(&prev, &current, &next);
        current = next;
    }
    if (alive[0] + alive[1] + alive[2] + alive[3] <= 1 || vm->proc == NULL)
        make_one_player_win(vm);
}

void live_process(virtual_machine_t *vm, proc_t *proc)
{
    int player_last_living UNUSED = 0;

    if (proc == NULL)
        return;
    vm->last_live = proc->player;
#ifndef GRAPHIC
    for (; player_last_living < 2; player_last_living++)
        if (vm->champion[player_last_living].prog_number == vm->last_live + 1)
            break;
    eprintf("The player %d (%s) is alive.\n", proc->player + 1,
            vm->champion[player_last_living].header.prog_name);
#endif
    proc->live = true;
    vm->live_count++;
    if (vm->live_count >= vm->cycle_to_die) {
        vm->live_count = 0;
        vm->cycle_to_die -= CYCLE_DELTA;
        death_sentence(vm);
    }
}

int live(virtual_machine_t *vm, proc_t *proc_unused UNUSED)
{
    int32_t param;
    proc_t *proc = vm->proc;

    load_args(&param, vm, proc, 1);
    while (proc) {
        if (proc->instance == (uint32_t)param)
            break;
        proc = proc->next;
    }
    live_process(vm, proc);
    return (1);
}
