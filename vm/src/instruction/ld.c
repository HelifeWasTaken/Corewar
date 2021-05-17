/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** ld
*/

#include <corewar/vm.h>

int get_arg_value(struct instruction *ins, int arg_i)
{
    uint8_t arg_type = ins->args_type[arg_i];
    char *arg = ins->params[arg_i].arg_pointer;

    if (arg_type == T_REG)
        return (arg[0]);
    else if (arg_type == T_DIR)
        return (arg[1] << 8 | arg[0]);
    else
        return (arg[3] << (8 * 3) | arg[2] << (8 * 2) | arg[1] << 8 | arg[0]);
}

void ld(virtual_machine_t *vm, proc_t *proc)
{
    int value = get_arg_value(&proc->instruction, 0);
}
