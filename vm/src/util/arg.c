/*
** EPITECH PROJECT, 2021
** arg
** File description:
** loader
*/

#include <corewar/vm.h>
#include <erty/eprintf.h>

static int32_t get_arg_value(struct instruction *ins, int arg_i,
        int pc UNUSED, struct memory *mem UNUSED)
{
    uint8_t arg_type = ins->args_type[arg_i];

    if (arg_type == T_REG)
        return (ins->params[arg_i].reg[0]);
    if ((OP_TAB[ins->opcode - 1].type[arg_i] & T_IDX) != 0 || arg_type == T_DIR)
        return (ins->params[arg_i].dir[0] << 8 | ins->params[arg_i].dir[1]);
    else
        return (ins->params[arg_i].ind[0] << 24 |
                ins->params[arg_i].ind[1] << 16 |
                ins->params[arg_i].ind[2] << 8 | ins->params[arg_i].ind[3]);
}

void load_args(int *param, virtual_machine_t *vm, proc_t *proc, int count)
{
    for (int8_t i = 0; i < count; i++)
        param[i] = get_arg_value(&proc->instruction, i,
                proc->pc.addr, vm->memory);
}
