/*
** EPITECH PROJECT, 2021
** jmp
** File description:
** jmp
*/

#include <corewar/vm.h>
#include <erty/eprintf.h>

int zjmp(virtual_machine_t *vm UNUSED, proc_t *proc)
{
    int32_t param = 0;

    load_args(&param, vm, proc, 1);
    //if (proc->carry != 0)
    //    return (0);
    proc->pc.next_addr = getindex(proc->pc.addr, param % IDX_MOD);
    return (1);
}
