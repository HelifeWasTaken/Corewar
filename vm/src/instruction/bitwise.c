/*
** EPITECH PROJECT, 2021
** bitwise
** File description:
** bits
*/

#include <corewar/vm.h>

int and(virtual_machine_t *vm UNUSED, proc_t *proc)
{
    int32_t args[3];
    int32_t res;

    load_args(args, vm, proc, 3);
    res = args[0] & args[1];
    ememcpy(proc->reg[args[2]], &res, REG_SIZE);
    return (res);
}

int or(virtual_machine_t *vm UNUSED, proc_t *proc)
{
    int32_t args[3];
    int32_t res;

    load_args(args, vm, proc, 3);
    res = args[0] | args[1];
    ememcpy(proc->reg[args[2]], &res, REG_SIZE);
    return (res);
}

int xor(virtual_machine_t *vm UNUSED, proc_t *proc)
{
    int32_t args[3];
    int32_t res;

    load_args(args, vm, proc, 3);
    res = args[0] ^ args[1];
    ememcpy(proc->reg[args[2]], &res, REG_SIZE);
    return (res);
}
