#include <corewar/vm.h>
#include <erty/ealloc.h>
    typedef struct proc {
        int8_t                  player;
        struct program_counter  pc;
        BYTE                    reg[REG_NUMBER][REG_SIZE];
        BYTE                    carry;
        struct proc             *next;
    } proc_t;

static struct proc *create_proc(struct proc *data)
{
    struct proc *new_proc = ecalloc(sizeof(struct proc), 1);

    new_proc->pc = data->pc;
    new_proc->player = data->player;
    return (new_proc);
}

void add_proc_back(struct proc **head, struct proc *data)
{
    struct proc *new_proc = create_proc(data);

    
}

void add_proc_front(struct proc *data)
{

}