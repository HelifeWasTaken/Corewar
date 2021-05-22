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
    #include "SFML/Audio.h"
    #include "corewar/op.h"
    #include "corewar/vm.h"

    #define RECT_SIZE 20

    typedef struct memoryrect {
        sfRectangleShape *ip[MEM_SIZE];
    } memoryrect_t;

    typedef struct menu {
        sfSprite *sprite;
        sfTexture *texture;
        sfMusic *music;
    } menu_t;

    void init_menu(menu_t *menu);
    void destroy_menu(menu_t *menu);

    typedef struct graph {
        sfRenderWindow *window;
        memoryrect_t memoryrect;
        sfView *view;
        struct {
            sfFont *font;
            sfText  *text;
        } text;
    } graph_t;

    void manage_graphical_event(graph_t *graph, sfEvent *event, bool *state);
    int manage_menu_event(graph_t *graph, menu_t *menu,
        sfEvent *event, bool *state);
    void create_graph(graph_t *graph);
    void destroy_graph(graph_t *graph);
    void update_memory(graph_t *graph, virtual_machine_t *vm);

#endif
