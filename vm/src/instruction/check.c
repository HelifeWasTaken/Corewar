/*
** EPITECH PROJECT, 2021
** check
** File description:
** instruction
*/

#include <corewar/vm.h>
#include <erty/estdlib.h>

static int count_args(BYTE opcode, uint8_t args_type[3])
{
    int i_arg_type = 0;
    BYTE flag = 0b11;

    ememset(args_type, 0, sizeof(uint8_t) * 3);
    for (int i = 0; i < 6; i += 2)
        args_type[i_arg_type++] = ((flag << i) & opcode) >> i;
    return ((bool)args_type[0] + (bool)args_type[1] + (bool)args_type[2]);
}

static bool check_arguments_instruction(proc_t *proc, BYTE opcode)
{
    for (unsigned int i = 0; i < proc->instruction.arg_count; i++)
        if ((proc->instruction.args_type[i] & OP_TAB[opcode - 1].type[i]) == 0)
            return (instruction_run_failed(proc));
    return (true);
}

static bool get_arguments_switch_process(proc_t *proc, struct memory *mem,
        int pc_offset, int i)
{
    switch (proc->instruction.args_type[i]) {
        case T_DIR:
            for (unsigned int dir_i = 0; dir_i < T_IND; dir_i++)
                proc->instruction.params[i].dir[dir_i] =
                    getmem_byte(proc->pc.addr, pc_offset, mem);
            return (true);
        case T_REG:
            proc->instruction.params[0].reg[0] =
                getmem_byte(proc->pc.addr, pc_offset, mem);
            return (proc->instruction.params[0].reg[0] <= REG_NUMBER &&
                    proc->instruction.params[0].reg[0] > 0);
        case T_IND:
            for (unsigned int ind_i = 0; ind_i < T_IND; ind_i++)
                proc->instruction.params[i].ind[ind_i] =
                    getmem_byte(proc->pc.addr, pc_offset, mem);
            return (true);
    }
    return (false);
}

static bool get_arguments_instructions(proc_t *proc, struct memory *mem)
{
    int pc_offset = proc->pc.addr + 2;

    for (unsigned int i = 0; i < proc->instruction.arg_count; i++) {
        if (get_arguments_switch_process(proc, mem, pc_offset, i) == false)
            return (false);
        pc_offset++;
    }
    proc->pc.next_addr = pc_offset;
    return (true);
}

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