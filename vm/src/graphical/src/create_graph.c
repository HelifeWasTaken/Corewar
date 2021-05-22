/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** create_graph
*/

#include "corewar/core.h"
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/View.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/VideoMode.h>
#include <SFML/Window/Window.h>
#include <stdlib.h>

void create_graph(graph_t *graph)
{
    graph->window = sfRenderWindow_create((sfVideoMode){ 1920, 1080, 64 },
            "corewar", sfClose, NULL);
    sfRenderWindow_setFramerateLimit(graph->window, 60);
    graph->text.font =
        sfFont_createFromFile("./src/graphical/asset/homespun.ttf");
    if (graph->text.font == NULL)
        exit (84);
    graph->text.text = sfText_create();
    sfText_setCharacterSize(graph->text.text, 15);
    sfText_setColor(graph->text.text, sfBlack);
    sfText_setFont(graph->text.text, graph->text.font);
    graph->view = sfView_create();
    for (unsigned int i = 0; i < MEM_SIZE; i++) {
        graph->memoryrect.ip[i] = sfRectangleShape_create();
        sfRectangleShape_setSize(graph->memoryrect.ip[i],
                (sfVector2f){RECT_SIZE, RECT_SIZE});
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
