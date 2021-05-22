/*
** EPITECH PROJECT, 2021
** fail
** File description:
** instruction
*/

#include <corewar/vm.h>

bool instruction_run_failed(proc_t *proc)
{
    proc->pc.cycle_count = 1;
    proc->pc.next_addr = (proc->pc.addr + 1) % MEM_SIZE;
    return (false);
}
