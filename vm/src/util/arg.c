/*
** EPITECH PROJECT, 2021
** arg
** File description:
** loader
*/

#include <corewar/vm.h>

static int32_t get_arg_value(struct instruction *ins, int arg_i,
        int pc, struct memory *mem)
{
    uint8_t arg_type = ins->args_type[arg_i];
    char *arg = ins->params[arg_i].arg_pointer;

    if (arg_type == T_REG)
        return (arg[0]);
    else if (arg_type == T_DIR)
        return (arg[1] << 8 | arg[0]);
    else
        return (getmem_byte(pc,
                    arg[3] << (8 * 3) | arg[2] << (8 * 2) |
                    arg[1] << 8 | arg[0], mem));
}

void load_args(int *param, virtual_machine_t *vm, proc_t *proc, int count)
{
    for (int8_t i = 0; i < count; i++)
        param[i] = get_arg_value(&proc->instruction, i,
                proc->pc.addr, vm->memory);
}
