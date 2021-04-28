/*
** EPITECH PROJECT, 2021
** VM
** File description:
** corewrar
*/

#ifndef _COREWAR_VM_H_
    #define _COREWAR_VM_H_

    #include <corewar/op.h>

    typedef struct vm {
        char reg[REG_NUMBER][REG_SIZE];
    } vm_t;

#endif
