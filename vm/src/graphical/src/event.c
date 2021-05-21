/*
** EPITECH PROJECT, 2020
** B-CPE-201-RUN-2-1-corewar-mattis.dalleau
** File description:
** event.c
*/

#include "corewar/core.h"

void manage_graphical_event(graph_t *graph, sfEvent *event, bool *state)
{
    while (sfRenderWindow_pollEvent(graph->window, event))
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(graph->window);
        else if (sfKeyboard_isKeyPressed(sfKeyEnter) == sfTrue)
            *state = true;
}

int manage_menu_event(graph_t *graph, menu_t *menu,
    sfEvent *event, bool *state)
{
    while (sfRenderWindow_pollEvent(graph->window, event)) {
        if (event->type == sfEvtClosed) {
            sfRenderWindow_close(graph->window);
            destroy_menu(menu);
            return (-1);
        }
        if (sfKeyboard_isKeyPressed(sfKeyEnter) == sfTrue)
            *state = true;
    }
    return (0);
}