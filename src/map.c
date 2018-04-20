/** @file map.c
 * @ingroup   Map
 * @defgroup  Map
 * @brief     The game's map handler.
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "map.h"

int8_t mapInit(const char *filename)
{
    tmx_map *map = tmx_load(filename);

    if (NULL == map) {
        tmx_perror("tmx_load");
        return -1;
    }

    return 0;
}

void mapTerminate(tmx_map *map)
{
    tmx_map_free(map);
}
