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
typedef struct map_t {
    const char  *filename;
    uint16_t    gidCenter;
    tmx_map     *tmx;
} Map;

Map    *mapInit();
int8_t mapLoadTmx(Map *map);
void   mapTerminate(Map *map);

#endif
