/*
** EPITECH PROJECT, 2021
** check
** File description:
** check
*/

#include <corewar/vm.h>

bool get_instruction_regular(vm_t *vm, proc_t *proc)
{
    BYTE opcode = proc->instruction.opcode;
    BYTE args = getmem_byte(proc->pc.addr, 1, vm->memory);

    proc->instruction.arg_count = count_args(args,
            proc->instruction.args_type);
    if (proc->instruction.arg_count != OP_TAB[opcode - 1].nbr_args)
        return (instruction_run_failed(proc));
    if (get_arguments_instructions(proc, vm->memory) == false)
        return (instruction_run_failed(proc));
    if (check_arguments_instruction(proc, opcode) == false)
        return (instruction_run_failed(proc));
    return (true);
}

bool get_instruction_special(vm_t *vm, proc_t *proc)
{
    proc->instruction.arg_count = 1;
    proc->instruction.args_type[0] = T_IND;
    for (unsigned int i = 0; i < T_IND; i++)
        proc->instruction.params[0].ind[i] =
            getmem_byte(proc->pc.addr + 1, i, vm->memory);
    proc->pc.next_addr = getindex(proc->pc.addr, 5);
    return (true);
}

bool get_instruction(vm_t *vm, proc_t *proc)
{
    BYTE opcode = getmem_byte(proc->pc.addr, 0, vm->memory);

    proc->instruction.opcode = opcode;
    if (opcode > OP_COUNT + 1 || opcode == 0)
        return (instruction_run_failed(proc));
    if (opcode == 0x9)
        return (get_instruction_special(vm, proc));
    else
        return (get_instruction_regular(vm, proc));
}
