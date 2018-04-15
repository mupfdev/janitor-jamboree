/* map.h -*-c-*-
 * Game map handler.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#ifndef MAP_h
#define MAP_h

#include <stdint.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

struct mapTile {
    uint8_t id;
    uint8_t type;
};

#endif
