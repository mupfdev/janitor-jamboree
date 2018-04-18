/** @file map.h
 * @ingroup   Map
 * @addtogrop Map
 */

#ifndef MAP_h
#define MAP_h

#include <stdint.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

/** @ingroup Map
 */
struct tileType {
    uint8_t id;
    uint8_t tilesetCoordX;
    uint8_t tilesetCoordY;
    uint8_t type;
};

typedef struct tileType tile;

struct mapType {
    const char  *file;
    tile        *mapData;
    SDL_Surface *mapSurface;
    const char  *tileset;
    uint16_t    startX;
    uint16_t    startY; 
    uint16_t    tilesNumX;
    uint16_t    tilesNumY;
};

typedef struct mapType map;

map *mapInit();
void mapTerminate(map *world);

#endif
