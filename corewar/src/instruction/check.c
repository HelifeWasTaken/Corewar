/*
** EPITECH PROJECT, 2021
** check
** File description:
** instruction
*/

#include <corewar/vm.h>
#include <erty/estdlib.h>
#include <stdlib.h>

int count_args(BYTE opcode, uint8_t args_type[3])
{
    ememset(args_type, 0, sizeof(uint8_t) * 3);
    args_type[0] = (opcode & 0b11000000) >> 6;
    args_type[1] = (opcode & 0b00110000) >> 4;
    args_type[2] = (opcode & 0b00001100) >> 2;
    args_type[0] = (args_type[0] == 0b1) ? T_REG :
        ((args_type[0] == 0b10) ? T_DIR : T_IND);
    if (args_type[1])
        args_type[1] = (args_type[1] == 0b1) ? T_REG :
            ((args_type[1] == 0b10) ? T_DIR : T_IND);
    if (args_type[2])
        args_type[2] = (args_type[2] == 0b1) ? T_REG :
            ((args_type[2] == 0b10) ? T_DIR : T_IND);
    return ((bool)args_type[0] + (bool)args_type[1] + (bool)args_type[2]);
}

bool check_arguments_instruction(proc_t *proc, BYTE opcode)
{
    for (unsigned int i = 0; i < proc->instruction.arg_count; i++)
        if ((proc->instruction.args_type[i] & OP_TAB[opcode - 1].type[i]) == 0)
            return (instruction_run_failed(proc));
    return (true);
}

static bool get_arguments_switch_process_second(proc_t *proc,
        struct memory *mem, int32_t *pc_offset, int i)
{
    if (OP_TAB[proc->instruction.opcode - 1].type[i] & T_IDX) {
        for (unsigned int dir_i = 0; dir_i < IND_SIZE; dir_i++) {
            proc->instruction.params[i].ind[dir_i] =
                getmem_byte(*pc_offset, 0, mem);
            (*pc_offset)++;
        }
        return (true);
    }
    if (proc->instruction.args_type[i] == T_DIR) {
        for (unsigned int dir_i = 0; dir_i < DIR_SIZE; dir_i++) {
            proc->instruction.params[i].dir[dir_i] =
                getmem_byte(*pc_offset, 0, mem);
            (*pc_offset)++;
        }
        return (true);
    }
    return (false);
}

static bool get_arguments_switch_process(proc_t *proc, struct memory *mem,
        int32_t *pc_offset, int i)
{
    if (get_arguments_switch_process_second(proc, mem, pc_offset, i) == true)
        return (true);
    if (proc->instruction.args_type[i] == T_REG) {
        proc->instruction.params[i].reg[0] = getmem_byte(*pc_offset, 0, mem);
        (*pc_offset)++;
        return (proc->instruction.params[i].reg[0] <= REG_NUMBER &&
                proc->instruction.params[i].reg[0] > 0);
    }
    if (proc->instruction.args_type[i] == T_IND) {
        for (unsigned int ind_i = 0; ind_i < IND_SIZE; ind_i++) {
            proc->instruction.params[i].ind[ind_i] =
                getmem_byte(*pc_offset, 0, mem);
            (*pc_offset)++;
        }
        return (true);
    }
    return (false);
}

bool get_arguments_instructions(proc_t *proc, struct memory *mem)
{
    int pc_offset = proc->pc.next_addr;

    if (!has_coding_byte(proc->instruction.opcode)) {
        get_arguments_switch_process(proc, mem, &pc_offset, 0);
        proc->pc.next_addr = pc_offset;
        return (true);
    }
    for (unsigned int i = 0; i < proc->instruction.arg_count; i++) {
        if (get_arguments_switch_process(proc, mem, &pc_offset, i) == false)
            return (false);
    }
    proc->pc.next_addr = pc_offset;
    return (true);
}
