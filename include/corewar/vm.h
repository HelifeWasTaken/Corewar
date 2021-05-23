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
    #include <erty/eprintf.h>
    #include <erty/eassert.h>

    typedef struct virtual_machine vm_t;

    typedef struct program_counter {
        int32_t addr;
        int32_t next_addr;
        int32_t cycle_count;
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
        int32_t prog_number;
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
            char reg[1];
            char dir[DIR_SIZE];
            char ind[IND_SIZE];
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
        uint32_t instance;
    } proc_t;

    void tick_procs(struct virtual_machine *vm);
    void add_proc_back(struct proc **head,
            struct proc *data, uint32_t *instance);
    void add_proc_front(struct proc **head,
            struct proc *data, uint32_t *instance);

    typedef struct virtual_machine {
        struct memory memory[MEM_SIZE];
        struct champion champion[CHAMPION_COUNT_MAX];
        unsigned int champion_count;
        struct proc *proc;
        struct {
            uint32_t last_instance;
            uint32_t cycle_to_die;
            uint32_t live_count;
            BYTE last_live;
        };
        struct {
            int32_t dump;
            int32_t cycle_before_dump;
        };
    } virtual_machine_t;

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

    int live(virtual_machine_t *vm, proc_t *proc);
    int ld(virtual_machine_t *vm, proc_t *proc);
    int lld(virtual_machine_t *vm, proc_t *proc);
    int ldi(virtual_machine_t *vm, proc_t *proc);
    int lldi(virtual_machine_t *vm, proc_t *proc);

    int st(virtual_machine_t *vm, proc_t *proc);
    int sti(virtual_machine_t *vm, proc_t *proc);

    int zjmp(virtual_machine_t *vm, proc_t *proc);

    int add(virtual_machine_t *vm UNUSED, proc_t *proc);
    int sub(virtual_machine_t *vm UNUSED, proc_t *proc);

    int and(virtual_machine_t *vm UNUSED, proc_t *proc);
    int or(virtual_machine_t *vm UNUSED, proc_t *proc);
    int xor(virtual_machine_t *vm UNUSED, proc_t *proc);

    int aff(virtual_machine_t *vm, proc_t *proc);

    int corewar_fork(virtual_machine_t *vm, proc_t *proc);
    int corewar_lfork(virtual_machine_t *vm, proc_t *proc);

    bool get_opt(char **argv, vm_t *vm, char ***champion_tab);
    int load_number_arg(char **av, int32_t *res, size_t *i, char *arg);
    bool get_opt_champion(vm_t *vm, char ***champion_tab,
            uint32_t *champion_index, char ***av);

    int core_loader(vm_t *vm, char **argv, int argc);

#endif
