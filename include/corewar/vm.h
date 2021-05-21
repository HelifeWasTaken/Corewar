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
    #include <erty/eendian.h>
    #include <erty/ebitwise.h>
    #include <erty/string/ecstring.h>

    typedef struct virtual_machine vm_t;

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
        struct header_s header;
        struct program_counter pc;
    } champion_t;

    typedef struct memory {
        BYTE byte;
        int8_t player;
    } memory_t;

    struct instruction {
        uint8_t arg_count;
        BYTE opcode;
        BYTE args_type[3];
        union {
            char reg[T_REG];
            char dir[T_DIR];
            char ind[T_IND];
            char *arg_pointer;
        } params[3];
    };

    typedef struct proc {
        int8_t player;
        struct program_counter pc;
        BYTE reg[REG_NUMBER][REG_SIZE];
        BYTE carry;
        struct proc *next;
        bool live;
        struct instruction instruction;
    } proc_t;

    void tick_procs(struct virtual_machine *vm);
    void add_proc_front(struct proc **head, struct proc *data);
    void add_proc_back(struct proc **head, struct proc *data);

    typedef struct virtual_machine {
        struct memory memory[MEM_SIZE];
        struct champion champion[CHAMPION_COUNT_MAX];
        unsigned int champion_count;
        struct proc *proc;
    } virtual_machine_t;

    #define DEFAULT_PROGRAM_COUNTER \
        (struct program_counter){ 0x0, HEADER_SIZE + 1, 0 }

    #define DEFAULT_CHAMPION \
        (struct champion){ \
            .header = { 0 }, \
            .pc = DEFAULT_PROGRAM_COUNTER, \
        }

    #define ACCESS_MEMORY(memory, idx) memory[(idx) % (MEM_SIZE)]

    bool vm_init(struct virtual_machine *vm, char **champion_files);

    bool vm_champion_init(struct virtual_machine *vm, char const *file,
        const unsigned int i, unsigned int count);

    struct memory_reader {
        const char *error;
        const int fd;
        const size_t offset;
        const size_t size;
        bool (*reader)(const int fd, void *mem, const size_t size);
    };

    bool read_memory_byte(const int fd, void *mem, const size_t size);
    bool read_memory_uint(const int fd, void *mem, size_t size);

    bool instruction_run_failed(proc_t *proc);

    int count_args(BYTE opcode, uint8_t args_type[3]);
    bool check_arguments_instruction(proc_t *proc, BYTE opcode);
    bool get_arguments_instructions(proc_t *proc, struct memory *mem);
    bool get_instruction_regular(vm_t *vm, proc_t *proc);
    bool get_instruction_special(vm_t *vm, proc_t *proc);
    bool get_instruction(vm_t *vm, proc_t *proc);

    int getindex(int pc, int offset);
    struct memory getmem(int pc, int offset, struct memory *mem);
    BYTE getmem_byte(int pc, int offset, struct memory *mem);
    int8_t getmem_player(int pc, int offset, struct memory *mem);
    #define PLAYER_AND_BYTE(player, byte) ((player) << 8 | (byte))
    void setmem(int pc, int offset, struct memory *mem, int16_t player_byte);

    bool has_coding_byte(BYTE opcode);
    void load_args(int *param, virtual_machine_t *vm, proc_t *proc, int count);

    void ld(virtual_machine_t *vm, proc_t *proc);
    void st(virtual_machine_t *vm, proc_t *proc);
    void zjmp(virtual_machine_t *vm, proc_t *proc);

#endif
