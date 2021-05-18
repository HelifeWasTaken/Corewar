/*
** EPITECH PROJECT, 2021
** jmp
** File description:
** jmp
*/

#include <corewar/vm.h>

void zjmp(virtual_machine_t *vm, proc_t *proc)
{
    int32_t param;

    load_args(&param, vm, proc, 1);
    proc->pc.next_addr = getindex(proc->pc.addr, param % IDX_MOD);
}
