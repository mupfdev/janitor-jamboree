/** @file config.h
 * @ingroup Config
 */

#ifndef CONFIG_h
#define CONFIG_h

#include <libconfig.h>
#include <stdint.h>

config_t configInit(config_t config, char *filename);
int32_t configGetBool(config_t config, const char *name);
int32_t configGetInt(config_t config, const char *name);
const char *configGetString(config_t config, const char *name);
void configTerminate(config_t config);

#endif
