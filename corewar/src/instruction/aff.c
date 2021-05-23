/*
** EPITECH PROJECT, 2021
** aff
** File description:
** corewar
*/

#include <corewar/vm.h>
#include <erty/estdio.h>

int aff(virtual_machine_t *vm UNUSED, proc_t *proc)
{
    int32_t value;

    ememcpy(&value, proc->reg[(int32_t)proc->instruction.params[0].reg[0]],
            sizeof(int32_t));
    eputchar(value % IDX_MOD);
    return (1);
}
