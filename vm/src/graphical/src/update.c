/* EPITECH PROJECT, 2021
** corewar
** File description:
** update
*/

#include "corewar/core.h"
#include "corewar/op.h"
#include "corewar/vm.h"
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <stdio.h>

static sfColor get_player_color(int8_t player)
{
    switch (player) {
        case 0:
            return (sfRed);
        case 1:
            return (sfYellow);
        case 2:
            return (sfBlue);
        case 3:
            return (sfMagenta);
    }
    return (sfColor_fromRGB(128, 128 , 128));
}

static sfColor get_champion_color(int8_t player)
{
    switch (player) {
        case 0:
            return (sfColor_fromRGB(185, 0, 0));
        case 1:
            return (sfColor_fromRGB(255, 185, 0));
        case 2:
            return (sfColor_fromRGB(0, 0, 185));
        case 3:
            return (sfColor_fromRGB(255, 0, 160));
    }
    return (sfWhite);
}

static void find_champion(graph_t *graph, virtual_machine_t *vm)
{
     for (proc_t *proc = vm->proc; proc != NULL; proc = proc->next) {
         sfRectangleShape_setFillColor(graph->memoryrect.ip[proc->pc.addr %
                MEM_SIZE], get_champion_color(proc->player));
        sfRenderWindow_drawRectangleShape(graph->window,
                graph->memoryrect.ip[proc->pc.addr % MEM_SIZE], NULL);
     }
}

static void find_memory_color(graph_t *graph, virtual_machine_t *vm)
{
    uint32_t x = 0;
    uint32_t y = 0;
    char buffer[4] = {0};

    for (uint32_t i = 0; i < MEM_SIZE; i++) {
        sfRectangleShape_setFillColor(graph->memoryrect.ip[i],
                get_player_color(vm->memory[i].player));
        sfRectangleShape_setPosition(graph->memoryrect.ip[i],
                (sfVector2f){x , y});
        snprintf(buffer, 3, "%02x", vm->memory[i].byte);
        sfText_setString(graph->text.text, buffer);
        sfText_setPosition(graph->text.text, (sfVector2f){x + 2, y});
        if (x >= 1920 - (RECT_SIZE - 2) * 2) {
            x = 0;
            y += RECT_SIZE + 2;
        } else
            x += RECT_SIZE + 2;
        sfRenderWindow_drawRectangleShape(graph->window,
                graph->memoryrect.ip[i], NULL);
        sfRenderWindow_drawText(graph->window, graph->text.text, NULL);
    }
}

void update_memory(graph_t *graph, virtual_machine_t *vm)
{
    find_memory_color(graph, vm);
    find_champion(graph, vm);
}
