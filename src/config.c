/* config.c -*-c-*-
 * Configuration handler.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#include "config.h"

config_t configInit(config_t config, char *filename)
{
    config_init(&config);

    if (NULL == filename)
        filename = "default.cfg";

    if (config_read_file(&config, filename) == CONFIG_FALSE)
    {
        fprintf(stderr, "%s\n", config_error_text(&config));
        config_destroy(&config);
    }

    return config;
}

int configGetBool(config_t config, const char *name)
{
    int value;

    if (config_lookup_bool(&config, name, &value) == CONFIG_FALSE)
        fprintf(stderr, "%s\n", config_error_text(&config));

    return value;
}

int configGetInt(config_t config, const char *name)
{
    int value;

    if (config_lookup_int(&config, name, &value) == CONFIG_FALSE)
        fprintf(stderr, "%s\n", config_error_text(&config));

    return value;
}

void configTerminate(config_t config)
{
    config_destroy(&config);
}
