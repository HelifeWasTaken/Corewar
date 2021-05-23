/*
** EPITECH PROJECT, 2021
** champion
** File description:
** open
*/

#include "champion_loader.h"

bool check_champion_stat_and_open(struct champion_loader *loader)
{
    loader->fd = open(loader->file, O_RDONLY);
    if (loader->fd == -1) {
        efprintf(stderr, "%s: Bad file descrpitor\n", loader->file);
        return (false);
    }
    return (true);
}
