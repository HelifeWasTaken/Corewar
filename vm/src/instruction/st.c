/*
** EPITECH PROJECT, 2021
** st
** File description:
** corewar
*/

#include <corewar/vm.h>

int st(virtual_machine_t *vm, proc_t *proc)
{
    int32_t param[2];
    int index = 0;
    mem32_t v;

    load_args(param, vm, proc, 2);
    if (proc->instruction.args_type[1] == T_DIR) {
        ememcpy(v.vmem, proc->reg[param[0]], REG_SIZE);
        v.vi = u32_swap_endian(v.vi);
        index = proc->pc.addr + param[1] % IDX_MOD;
        for (uint8_t i = 0; i < REG_SIZE; i++)
            setmem(proc->pc.addr, index + i, vm->memory,
                    PLAYER_AND_BYTE(proc->player, v.vmem[i]));
    } else {
        ememcpy(proc->reg[param[0]], proc->reg[param[1]], REG_SIZE);
    }
    return (1);
}

int sti(virtual_machine_t *vm, proc_t *proc)
{
    int32_t param[3];
    int32_t index = 0;
    int32_t param_res[2];
    mem32_t v;

    load_args(param, vm, proc, 3);
    param_res[0] = proc->instruction.args_type[1] != T_REG ?
        param[1] : *(int32_t *)proc->reg[param[1]];
    param_res[1] = proc->instruction.args_type[1] != T_REG ?
        param[1] : *(int32_t *)proc->reg[param[2]];
    ememcpy(v.vmem, proc->reg[param[0]], REG_SIZE);
    v.vi = u32_swap_endian(v.vi);
    index = proc->pc.addr + (param_res[0] + param_res[1]) % IDX_MOD;
    for (uint8_t i = 0; i < REG_SIZE; i++)
        setmem(proc->pc.addr, index + i, vm->memory,
                PLAYER_AND_BYTE(proc->player, v.vmem[i]));
    return (1);
}
