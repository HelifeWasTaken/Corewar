/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** core.h
*/

#ifndef CORE_H
    #define CORE_H

    #include <SFML/Graphics.h>
    #include <SFML/Graphics/Color.h>
    #include <SFML/Graphics/Types.h>
    #include <SFML/System/Vector2.h>
    #include "corewar/op.h"
    #include "corewar/vm.h"

    #define RECT_SIZE 20

    enum player_color {
        PLAYER_ONE_COLOR = 4278190335,
        PLAYER_TWO_COLOR = 65535,
        PLAYER_THIRD_COLOR = 4294902015,
        PLAYER_FOUR_COLOR = 4278255615
    };

    typedef struct memoryrect {
        sfRectangleShape *ip[MEM_SIZE];
    } memoryrect_t;

    typedef struct graph {
        sfRenderWindow *window;
        memoryrect_t memoryrect;
        struct {
            sfFont *font;
            sfText  *text;
        } text;
    } graph_t;

    void create_graph(graph_t *graph);
    void update_memory(graph_t *graph, virtual_machine_t *vm);

#endif
