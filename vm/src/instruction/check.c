/*
** EPITECH PROJECT, 2021
** check
** File description:
** instruction
*/

#include <corewar/vm.h>
#include <erty/estdlib.h>

static int count_args_from_opcode(BYTE opcode, uint8_t args_type[3])
{
    int i_arg_type = 0;
    BYTE flag = 0b11;

    for (int i = 6; i > 0; i -= 2)
        args_type[i_arg_type++] = ((flag << i) & opcode) >> i;
    return ((bool)args_type[0] + (bool)args_type[1] + (bool)args_type[2]);
}

static bool check_arguments_instruction(proc_t *proc, BYTE opcode)
{
    for (unsigned int i = 0; i < proc->instruction.arg_count; i++)
        if ((proc->instruction.args_type[i] & OP_TAB[opcode].type[i]) == 0)
            return (instruction_run_failed(proc));
    return (true);
}

static bool get_arguments_switch_process(proc_t *proc, struct memory *mem,
        int *pc_offset, int i)
{
    switch (proc->instruction.args_type[i]) {
    case T_DIR:
        for (unsigned int dir_i = 0; dir_i < T_IND; dir_i++)
            proc->instruction.params[i].dir[dir_i] = mem[(*pc_offset)++].byte;
        return (true);
    case T_REG:
        proc->instruction.params[0].reg[0] = mem[(*pc_offset)++].byte;
        return (proc->instruction.params[0].reg[0] <= REG_NUMBER &&
                proc->instruction.params[0].reg > 0);
    case T_IND:
        for (unsigned int ind_i = 0; ind_i < T_IND; ind_i++)
            proc->instruction.params[i].ind[ind_i] = mem[(*pc_offset)++].byte;
        return (true);
    }
    return (false);
}

static bool get_arguments_instructions(proc_t *proc, struct memory *mem)
{
    int pc_offset = proc->pc.addr;

    for (unsigned int i = 0; i < proc->instruction.arg_count; i++)
        if (get_arguments_switch_process(proc, mem, &pc_offset, i) == false)
            return (false);
    proc->pc.next_addr = pc_offset;
    return (true);
}

bool get_instruction(vm_t *vm, proc_t *proc)
{
    BYTE pc_byte = vm->memory[proc->pc.addr].byte;
    BYTE opcode = (0b110000 & pc_byte) >> 6;

    proc->instruction.arg_count = count_args_from_opcode(pc_byte,
            proc->instruction.args_type);
    if (opcode > ARRAY_SIZE(OP_TAB))
        return (instruction_run_failed(proc));
    if (proc->instruction.arg_count != OP_TAB[opcode].nbr_args)
        return (instruction_run_failed(proc));
    if (get_arguments_instructions(proc, vm->memory) == false)
        return (instruction_run_failed(proc));
    if (check_arguments_instruction(proc, opcode) == false)
        return (instruction_run_failed(proc));
    return (true);
}
