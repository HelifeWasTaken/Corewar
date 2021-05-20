/*
** EPITECH PROJECT, 2021
** main.c
** File description:
** corewar
*/

#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Window.h>
#include <erty/ectypes.h>
#include <corewar/vm.h>
#include "corewar/core.h"
#include "corewar/op.h"

void starting_loop(graph_t *graph, virtual_machine_t *vm)
{
    sfEvent event;

    while (sfRenderWindow_isOpen(graph->window)) {
        sfRenderWindow_clear(graph->window, sfBlack);
        while (sfRenderWindow_pollEvent(graph->window, &event))
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(graph->window);
        update_memory(graph, vm);
        tick_procs(vm);
        sfRenderWindow_display(graph->window);
    }
}

void destroy_graph(graph_t *graph)
{
    for (int i = 0; i < MEM_SIZE; i++)
            sfRectangleShape_destroy(graph->memoryrect.ip[i]);
    sfText_destroy(graph->text.text);
    sfFont_destroy(graph->text.font);
    sfRenderWindow_destroy(graph->window);
}

int main(int ac UNUSED, char **av UNUSED)
{
    virtual_machine_t vm = {0};
    graph_t graph = {0};

    if (ac <= 1)
        return (EXIT_FAILURE);
    if (vm_init(&vm, av + 1) == false)
        return (EXIT_FAILURE);
    create_graph(&graph);
    starting_loop(&graph, &vm);
    destroy_graph(&graph);
    return (0);
}
