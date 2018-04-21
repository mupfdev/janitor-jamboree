/** @file map.h
 * @ingroup   Map
 * @addtogrop Map
 */

#ifndef MAP_h
#define MAP_h

#include <tmx.h>
#include <SDL2/SDL.h>

/** @ingroup Map
 */
struct MapType {
    SDL_Surface *tileset;
    tmx_map     *tmxMap;
};

typedef struct MapType Map;

Map *mapInit();
void mapTerminate(Map *map);

#endif
