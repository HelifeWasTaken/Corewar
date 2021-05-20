/*
** EPITECH PROJECT, 2021
** champion
** File description:
** open
*/

#include "champion_loader.h"

bool check_champion_stat_and_open(struct stat *st,
        struct champion_loader *loader)
{
    if (stat(loader->file, st) == -1) {
        efprintf(stderr, "%s: Stat failed\n", loader->file);
        return (false);
    }
    if ((st->st_mode & S_IFMT) != S_IFREG) {
        efprintf(stderr, "%s: Not a regular file\n", loader->file);
        return (false);
    }
    loader->fd = open(loader->file, O_RDONLY);
    if (loader->fd == -1) {
        efprintf(stderr, "%s: Bad file descrpitor\n", loader->file);
        return (false);
    }
    return (true);
}
