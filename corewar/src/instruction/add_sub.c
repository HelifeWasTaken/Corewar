/*
** EPITECH PROJECT, 2021
** add
** File description:
** core
*/

#include <corewar/vm.h>

int add(virtual_machine_t *vm UNUSED, proc_t *proc)
{
    int32_t param[2] = {0};
    int32_t res = 0;

    ememcpy(&param[0],
            proc->reg[(int32_t)proc->instruction.params[0].reg[0]], REG_SIZE);
    ememcpy(&param[1],
            proc->reg[(int32_t)proc->instruction.params[1].reg[0]], REG_SIZE);
    res = param[0] + param[1];
    ememcpy(proc->reg[(int32_t)proc->instruction.params[2].reg[0]],
            &res, REG_SIZE);
    return (res);
}

int sub(virtual_machine_t *vm UNUSED, proc_t *proc)
{
    int32_t param[2] = {0};
    int32_t res = 0;

    ememcpy(&param[0],
            proc->reg[(int32_t)proc->instruction.params[0].reg[0]], REG_SIZE);
    ememcpy(&param[1],
            proc->reg[(int32_t)proc->instruction.params[1].reg[0]], REG_SIZE);
    res = param[0] - param[1];
    ememcpy(proc->reg[(int32_t)proc->instruction.params[2].reg[0]],
            &res, REG_SIZE);
    return (res);
}
