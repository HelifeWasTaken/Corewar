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

    if (has_coding_byte(proc->instruction.opcode)) {
        proc->instruction.arg_count = count_args(getmem_byte(proc->pc.addr,
            1, vm->memory), proc->instruction.args_type);
        if (proc->instruction.arg_count != OP_TAB[opcode - 1].nbr_args)
            return (instruction_run_failed(proc));
    }
    if (get_arguments_instructions(proc, vm->memory) == false)
        return (instruction_run_failed(proc));
    if (check_arguments_instruction(proc, opcode) == false)
        return (instruction_run_failed(proc));
    return (true);
}

bool get_instruction(vm_t *vm, proc_t *proc)
{
    BYTE opcode = getmem_byte(proc->pc.addr, 0, vm->memory);

    proc->instruction.opcode = opcode;
    if (opcode > OP_COUNT + 1 || opcode == 0)
        return (instruction_run_failed(proc));
    return (get_instruction_regular(vm, proc));
}
