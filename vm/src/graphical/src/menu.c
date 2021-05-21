/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** menu
*/

#include "corewar/core.h"
#include <SFML/Audio/Music.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>

void init_menu(menu_t *menu)
{
    menu->sprite = sfSprite_create();
    menu->texture =
        sfTexture_createFromFile("./src/graphical/asset/window_xp.png", NULL);
    sfSprite_setTexture(menu->sprite, menu->texture, false);
    menu->music =
        sfMusic_createFromFile("./src/graphical/asset/window_xp_sound.ogg");
}

void destroy_menu(menu_t *menu)
{
    sfSprite_destroy(menu->sprite);
    sfTexture_destroy(menu->texture);
    sfMusic_destroy(menu->music);
}
