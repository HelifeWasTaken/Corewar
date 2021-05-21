/*
** EPITECH PROJECT, 2021
** arg
** File description:
** loader
*/

#include <corewar/vm.h>

static int32_t get_arg_value(struct instruction *ins, int arg_i,
        int pc UNUSED, struct memory *mem UNUSED)
{
    uint8_t arg_type = ins->args_type[arg_i];
    char *arg = ins->params[arg_i].arg_pointer;

    if ((OP_TAB[ins->opcode - 1].type[arg_i] & T_IDX) != 0 || arg_type == T_DIR)
        return (arg[0] << 8 | arg[1]);
    else if (arg_type == T_REG)
        return (arg[0]);
    else
        return (arg[0] << (8 * 3) | arg[1] << (8 * 2) |
                arg[2] << 8 | arg[3]);
}

void load_args(int *param, virtual_machine_t *vm, proc_t *proc, int count)
{
    for (int8_t i = 0; i < count; i++)
        param[i] = get_arg_value(&proc->instruction, i,
                proc->pc.addr, vm->memory);
}
