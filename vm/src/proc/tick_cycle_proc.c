/*
** EPITECH PROJECT, 2021
** tick
** File description:
** cyles
*/

#include <corewar/vm.h>
#include <erty/estdlib.h>

void run_instruction(virtual_machine_t *vm, proc_t *proc)
{
    int (*instruction[OP_COUNT])(virtual_machine_t *, proc_t *) = {
        NULL, &ld, &st, &add, &sub, &and,
        &or, &xor, &zjmp, &ldi, &sti, &corewar_fork,
        &lld, &lldi, &corewar_lfork, &aff
    };

    if (instruction[proc->instruction.opcode - 1] != NULL)
        instruction[proc->instruction.opcode - 1](vm, proc);
    else
        instruction_run_failed(proc);
}

static void get_new_cycle(struct memory *mem, proc_t *proc)
{
    BYTE opcode = getmem_byte(proc->pc.addr, 0, mem);

    if (opcode > OP_COUNT + 1) {
        proc->pc.cycle_count = 1;
    } else {
        proc->pc.cycle_count = OP_TAB[opcode - 1].nbr_cycles;
    }
}

void tick_procs(vm_t *vm)
{
    for (proc_t *proc = vm->proc; proc; proc = proc->next) {
        if (proc->pc.cycle_count > 0) {
            proc->pc.cycle_count--;
            continue;
        }
        if (get_instruction(vm, proc) == true) {
            run_instruction(vm, proc);
            proc->pc.addr = getindex(proc->pc.next_addr, 0);
            get_new_cycle(vm->memory, proc);
        } else
            proc->pc.addr = getindex(proc->pc.next_addr, 0);
    }
}
