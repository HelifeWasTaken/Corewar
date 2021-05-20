/*
** EPITECH PROJECT, 2021
** jmp
** File description:
** jmp
*/

#include <corewar/vm.h>
#include <erty/eprintf.h>

void zjmp(virtual_machine_t *vm UNUSED, proc_t *proc)
{
    char *ptr = proc->instruction.params[0].ind;
    int32_t param = ptr[0] << 8 | ptr[1];

    proc->pc.next_addr = getindex(proc->pc.addr, param % IDX_MOD);
}
