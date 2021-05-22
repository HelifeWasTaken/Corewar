/*
** EPITECH PROJECT, 2021
** fork
** File description:
** fork
*/

#include <corewar/vm.h>

int corewar_fork(virtual_machine_t *vm, proc_t *proc)
{
    int param;
    proc_t new_proc = {0};

    load_args(&param, vm, proc, 1);
    new_proc.pc.addr = proc->pc.addr + param % IDX_MOD;
    new_proc.player = proc->player;
    add_proc_front(&vm->proc, &new_proc);
    return (1);
}

int corewar_lfork(virtual_machine_t *vm, proc_t *proc)
{
    int param;
    proc_t new_proc = {0};

    load_args(&param, vm, proc, 1);
    new_proc.pc.addr = proc->pc.addr + param;
    new_proc.player = proc->player;
    add_proc_front(&vm->proc, &new_proc);
    return (1);
}
