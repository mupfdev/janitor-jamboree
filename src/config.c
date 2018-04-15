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
        filename = "game.cfg";

    if (CONFIG_FALSE == config_read_file(&config, filename))
    {
        fprintf(stderr, "%s\n", config_error_text(&config));
        config_destroy(&config);
    }

    return config;
}

int configGetBool(config_t config, const char *name)
{
    int value;

    if (CONFIG_FALSE == config_lookup_bool(&config, name, &value))
        fprintf(stderr, "%s\n", config_error_text(&config));

    return value;
}

int configGetInt(config_t config, const char *name)
{
    int value;

    if (CONFIG_FALSE == config_lookup_int(&config, name, &value))
        fprintf(stderr, "%s\n", config_error_text(&config));

    return value;
}

const char *configGetString(config_t config, const char *name)
{
    const char *value;

    if (CONFIG_FALSE == config_lookup_string (&config, name, &value))
        fprintf(stderr, "%s\n", config_error_text(&config));

    return value;
}

void configTerminate(config_t config)
{
    config_destroy(&config);
}
