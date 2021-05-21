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

    load_args(param, vm, proc, 2);
    if (proc->instruction.args_type[1] == T_DIR) {
        index = proc->pc.addr + param[1] % IDX_MOD;
        for (uint8_t i = 0; i < REG_SIZE; i++)
            setmem(proc->pc.addr, index + i, vm->memory,
                    PLAYER_AND_BYTE(proc->player, proc->reg[param[0]][i]));
    } else
        ememcpy(proc->reg[param[0]], proc->reg[param[1]], REG_SIZE);
    return (1);
}
