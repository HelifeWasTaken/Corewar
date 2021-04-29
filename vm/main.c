/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#include <erty/getopt.h>
#include <erty/string/esstring.h>
#include <stdlib.h>

/*
bool load_args(my_getopt_t *my_args, char **argv)
{
    ememset(my_args, 0, sizeof(my_getopt_t));
    my_args->arg[0] = OPT_ARG(NULL, "-dump", false, OPT_INT);
    my_args->arg[1] = OPT_ARG("-n", NULL, false, OPT_INT);
    my_args->arg[2] = OPT_ARG("-a", NULL, false, OPT_INT);
    my_args->arg[3] = OPT_ARG(NULL, NULL, false, OPT_NO_ARG);
    return (my_getopt(my_args, argv));
}
*/

void *set_memory_zero(void *ptr, size_t size)
{
    char *ptr_to_set = (char *)ptr;

    for (size_t i = 0; i < size; i++)
        ptr_to_set[i] = 0;
    return (ptr);
}

void display_memory(void *ptr, size_t size)
{
    char *ptr_to_set = (char *)ptr;

    for (size_t i = 0; i < size; i++)
        printf("%ld: [%d|0x%x]\n", i, ptr_to_set[i], ptr_to_set[i]);
}

void *my_calloc(size_t size)
{
    void *ptr = malloc(size);

    display_memory(ptr, size);
    printf("------\n");
    set_memory_zero(ptr, size);
    display_memory(ptr, size);
    return (ptr);
}

int main(int ac UNUSED, char **av UNUSED)
{
    void *ptr = my_calloc(10);
    (void)ptr;
    return (0);
}
