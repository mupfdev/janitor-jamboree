/** @file map.h
 * @ingroup   Map
 * @addtogrop Map
 */

#ifndef MAP_h
#define MAP_h

#include <stdint.h>
#include <tmx.h>

int8_t mapInit(const char *filename);
void mapTerminate(tmx_map *map);

#endif
