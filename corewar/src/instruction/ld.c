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
    v.vi = u32_swap_endian(v.vi);
    ememcpy(proc->reg[param[1]], v.vmem, sizeof(int32_t));
    return (v.vi);
}

int lld(virtual_machine_t *vm, proc_t *proc)
{
    int32_t param[2];
    int32_t index;
    mem32_t v;

    load_args(param, vm, proc, 2);
    index = proc->pc.addr + param[0];
    for (uint8_t i = 0; i < REG_SIZE; i++)
        v.vmem[i] = getmem_byte(proc->pc.addr, index + i, vm->memory);
    v.vi = u32_swap_endian(v.vi);
    ememcpy(proc->reg[param[1]], v.vmem, sizeof(int32_t));
    return (v.vi);
}

int ldi(virtual_machine_t *vm, proc_t *proc)
{
    int32_t param[3];
    int32_t index;
    mem32_t v;
    mem16_t indv;

    load_args(param, vm, proc, 3);
    for (uint8_t i = 0; i < IND_SIZE; i++)
        indv.vmem[i] = getmem_byte(proc->pc.addr, param[0] + i, vm->memory);
    indv.vi = u16_swap_endian(indv.vi) + param[1];
    index = proc->pc.addr + indv.vi % IDX_MOD;
    for (uint8_t i = 0; i < REG_SIZE; i++)
        v.vmem[i] = getmem_byte(proc->pc.addr, index + i, vm->memory);
    v.vi = u32_swap_endian(v.vi);
    ememcpy(proc->reg[param[2]], v.vmem, sizeof(int32_t));
    return (v.vi);
}

int lldi(virtual_machine_t *vm, proc_t *proc)
{
    int32_t param[3];
    int32_t index;
    mem32_t v;
    mem16_t indv;

    load_args(param, vm, proc, 3);
    for (uint8_t i = 0; i < IND_SIZE; i++)
        indv.vmem[i] = getmem_byte(proc->pc.addr, param[0] + i, vm->memory);
    indv.vi = u16_swap_endian(indv.vi) + param[1];
    index = proc->pc.addr + indv.vi;
    for (uint8_t i = 0; i < REG_SIZE; i++)
        v.vmem[i] = getmem_byte(proc->pc.addr, index + i, vm->memory);
    v.vi = u32_swap_endian(v.vi);
    ememcpy(proc->reg[param[2]], v.vmem, sizeof(int32_t));
    return (v.vi);
}
