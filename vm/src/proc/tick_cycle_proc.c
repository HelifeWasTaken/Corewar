/*
** EPITECH PROJECT, 2021
** tick
** File description:
** cyles
*/

#include <corewar/vm.h>

void tick_procs(vm_t *vm)
{
    for (proc_t *proc = vm->proc; proc; proc = proc->next) {
        if (proc->pc.cycle_count > 0) {
            proc->pc.cycle_count--;
            continue;
        }
        if (get_instruction(vm, proc) == true)
            run_instruction(vm, proc);
        proc->pc.addr = proc->pc.next_addr;
    }
}
