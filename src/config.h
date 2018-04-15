/* config.h -*-c-*-
 * Configuration handler.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#ifndef CONFIG_h
#define CONFIG_h

#include <libconfig.h>
#include <stdint.h>

config_t configInit(config_t config, char *filename);
int configGetBool(config_t config, const char *name);
int configGetInt(config_t config, const char *name);
const char *configGetString(config_t config, const char *name);
void configTerminate(config_t config);

#endif
