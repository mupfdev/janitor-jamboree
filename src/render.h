/** @file render.h
 * @ingroup   Render
 * @defgroup  Render
 * @brief     The game's graphics renderer.
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#ifndef RENDER_h
#define RENDER_h

#include <stdint.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "player.h"

int8_t render(SDL_Surface *screen, Player *player);

#endif
