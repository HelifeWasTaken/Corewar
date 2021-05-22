/*
** EPITECH PROJECT, 2021
** header
** File description:
** header
*/

#include <corewar/vm.h>
#include <erty/ealloc.h>

static struct proc *create_proc(struct proc *data, uint32_t *instance)
{
    struct proc *new_proc = ecalloc(sizeof(struct proc), 1);

    new_proc->pc = data->pc;
    new_proc->player = data->player;
    new_proc->instance = *instance;
    (*instance)++;
    return (new_proc);
}

void add_proc_back(struct proc **head, struct proc *data, uint32_t *instance)
{
    struct proc *new_proc = create_proc(data, instance);
    struct proc *ptr = *head;

    if (*head == NULL) {
        *head = new_proc;
        return;
    }
    for (; ptr->next; ptr = ptr->next);
    ptr->next = new_proc;
}

void add_proc_front(struct proc **head, struct proc *data, uint32_t *instance)
{
    struct proc *new_proc = create_proc(data, instance);

    new_proc->next = *head;
    *head = new_proc;
}
