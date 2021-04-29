/*
** EPITECH PROJECT, 2021
** VM
** File description:
** corewar
*/

#ifndef _COREWAR_VM_H_
    #define _COREWAR_VM_H_

    #include <corewar/op.h>
    #include <stdbool.h>

    enum living {
        DEAD,
        WAITING_LIVE,
        LIVING
    };

    typedef struct program_counter {
        unsigned int addr;
        unsigned int next_addr;
        unsigned int cycle_count;
    } program_counter_t;

    //
    // The carry is the Register where the return of the conditional is stored
    // For example
    // sti r1, %:live,%1
    // zjmp %:live
    //

    typedef struct champion {
        struct      header_s header;
        struct      program_counter pc;
        int         fd;
        BYTE        carry;
        enum living live;
    } champion_t;

    typedef struct virtual_machine {
        BYTE            reg[REG_NUMBER][REG_SIZE];
        BYTE            memory[MEM_SIZE];
        struct champion champion[CHAMPION_COUNT_MAX];
        unsigned int    champion_count;
    } virtual_machine_t;

    #define DEFAULT_PROGRAM_COUNTER \
        (struct program_counter){ 0x0, HEADER_SIZE + 1, 0 }

    #define DEFAULT_CHAMPION \
        (struct champion){ \
            .header = { 0 }, \
            .pc     = DEFAULT_PROGRAM_COUNTER, \
            .fd     = -1, \
            .carry  =  0, \
            .live = WAITING_LIVE \
        }

    #define ACCESS_MEMORY(memory, idx) memory[(idx) % (MEM_SIZE)]

    bool vm_champion_init(struct champion *champion, char const *file);

#endif
