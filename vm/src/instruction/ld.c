/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** ld
*/

#include <corewar/vm.h>

int ld(virtual_machine_t *vm, proc_t *proc)
{
    int32_t param[2];
    int32_t index;
    mem32_t v;

    load_args(param, vm, proc, 2);
    index = proc->pc.addr + param[0] % IDX_MOD;
    for (uint8_t i = 0; i < REG_SIZE; i++)
        v.vmem[i] = getmem_byte(proc->pc.addr, index + i, vm->memory);
    ememcpy(proc->reg[param[1]], v.vmem, sizeof(int32_t));
    return (1);
}
