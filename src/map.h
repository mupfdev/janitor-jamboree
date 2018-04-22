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
    const char  *filename;
    tmx_map     *tmx;
};

typedef struct MapType Map;

Map    *mapInit();
int8_t mapLoadTmx(Map *map);
void   mapTerminate(Map *map);

#endif
