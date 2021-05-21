/*
** EPITECH PROJECT, 2021
** main.c
** File description:
** corewar
*/

#include <SFML/Config.h>
#include <stdio.h>
#include <SFML/Audio/Music.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Keyboard.h>
#include <SFML/Window/Window.h>
#include <erty/ectypes.h>
#include <corewar/vm.h>
#include "corewar/core.h"
#include "corewar/op.h"

static void graphic_loop(graph_t *graph, virtual_machine_t *vm, bool *state)
{
    sfEvent event;

    while (sfRenderWindow_isOpen(graph->window)) {
        sfRenderWindow_clear(graph->window, sfBlack);
        manage_graphical_event(graph, &event, state);
        update_memory(graph, vm);
        tick_procs(vm);
        sfRenderWindow_display(graph->window);
    }
}

static int menu_loop(graph_t *graph, menu_t *menu, bool *state)
{
    init_menu(menu);
    sfEvent event;
    sfMusic_play(menu->music);
    while (*state == false) {
        sfRenderWindow_clear(graph->window, sfBlack);
        if (manage_menu_event(graph, menu, &event, state) == -1)
            return (-1);
        sfRenderWindow_drawSprite(graph->window, menu->sprite, NULL);
        sfRenderWindow_display(graph->window);
    }
    destroy_menu(menu);
    return (0);
}

void base_loop(graph_t *graph, menu_t *menu, virtual_machine_t *vm)
{
    bool state = false;

    while (sfRenderWindow_isOpen(graph->window)) {
        if (state == false) {
            if (menu_loop(graph, menu, &state) == -1)
                return;
        } else
            graphic_loop(graph, vm, &state);
    }
}

int main(int ac UNUSED, char **av UNUSED)
{
    virtual_machine_t vm = {0};
    graph_t graph = {0};
    menu_t menu = {0};

    if (ac <= 1)
        return (EXIT_FAILURE);
    if (vm_init(&vm, av + 1) == false)
        return (EXIT_FAILURE);
    create_graph(&graph);
    base_loop(&graph, &menu, &vm);
    destroy_graph(&graph);
    return (0);
}
