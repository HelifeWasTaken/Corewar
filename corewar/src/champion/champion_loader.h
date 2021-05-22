/*
** EPITECH PROJECT, 2021
** champion_loader
** File description:
** champion
*/

#ifndef __COREWAR__CHAMPION__LOADER__H__
    #define __COREWAR__CHAMPION__LOADER__H__

    #include <corewar/vm.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <erty/estdlib.h>
    #include <erty/eprintf.h>
    #include <stdbool.h>

    struct champion_loader {
        int fd;
        const unsigned int i;
        const unsigned int count;
        const char *file;
    };

    bool vm_champion_init(struct virtual_machine *vm, char const *file,
        const unsigned int i, unsigned int count);
    bool check_champion_stat_and_open(struct stat *st,
        struct champion_loader *loader);
    bool vm_write_champion_in_ram(struct virtual_machine *vm,
        struct champion_loader *loader);

#endif
