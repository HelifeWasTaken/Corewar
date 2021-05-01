/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#include <erty/getopt.h>
#include <erty/string/esstring.h>
#include <stdlib.h>
#include <corewar/vm.h>

int main(int ac UNUSED, char **av UNUSED)
{
    struct virtual_machine vm = {0};

    if (ac == 1)
        return (84);
    vm_init(&vm, av + 1);
    //write(1, &vm.champion[0].header, sizeof(struct header_s));
    printf("0x%x\n", vm.champion[0].header.magic);
    printf("%s\n", vm.champion[0].header.prog_name);
    printf("%d\n", vm.champion[0].header.prog_size);
    printf("%s\n", vm.champion[0].header.comment);
    return (0);
}
