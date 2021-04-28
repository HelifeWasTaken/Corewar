/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#include <erty/getopt.h>

bool load_args(my_getopt_t *my_args, char **argv)
{
    ememset(my_args, 0, sizeof(my_getopt_t));
    my_args->arg[0] = OPT_ARG(NULL, "-dump", false, OPT_INT);
    my_args->arg[1] = OPT_ARG("-n", NULL, false, OPT_INT);
    my_args->arg[2] = OPT_ARG("-a", NULL, false, OPT_INT);
    my_args->arg[3] = OPT_ARG(NULL, NULL, false, OPT_NO_ARG);
    return (my_getopt(my_args, argv));
}

int main(int ac UNUSED, char **av UNUSED)
{
    int n = 5;
    /*
    my_getopt_t my_args = {0};

    if (load_args(&my_args, av) == false) {
        destroy_opts(&my_args);
        eprintf_free_buff();
        return (84);
    }
    display_opts(&my_args);
    destroy_opts(&my_args);
    */
    eprintf("%m", &n, sizeof(int));
    eprintf_free_buff();
    return (0);
}
