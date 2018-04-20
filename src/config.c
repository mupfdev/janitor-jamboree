/** @file config.c
 * @ingroup   Config
 * @defgroup  Config
 * @brief     Configuration file handler.
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "config.h"

/**
 * @brief   Initialise a configuration file.
 * @param   config The structure which needs to be initialised.
 * @param   filename Path to the configuration file.
 * @return  Initialised config_t structure.  Deallocating all memory associated
 *          with the configuration on error, but does not attempt to deallocate
 *          the config_t structure itself.
 * @todo    Adjust function to return pointer instead of config_t structure.
 * @ingroup Config
 */
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

/**
 * @brief   Look up a boolean value specified by @e name. @e
 * @param   config Initialised config_t structure.
 * @param   name Name of the requested value.
 * @return  value The requested boolean value, prints message on error.
 * @ingroup Config
 */
int32_t configGetBool(config_t config, const char *name)
{
    int value;

    if (CONFIG_FALSE == config_lookup_bool(&config, name, &value))
        fprintf(stderr, "%s\n", config_error_text(&config));

    return value;
}

/**
 * @brief   Look up a integer specified by @e name. @e
 * @param   config Initialised config_t structure.
 * @param   name Name of the requested integer.
 * @return  value The requested integer, prints message on error.
 * @ingroup Config
 */
int32_t configGetInt(config_t config, const char *name)
{
    int value;

    if (CONFIG_FALSE == config_lookup_int(&config, name, &value))
        fprintf(stderr, "%s\n", config_error_text(&config));

    return value;
}

/**
 * @brief   Look up a string value specified by @e name. @e
 * @param   config Initialised config_t structure.
 * @param   name Name of the requested string.
 * @return  value The requested string, prints message on error.
 * @ingroup Config
 */
const char *configGetString(config_t config, const char *name)
{
    const char *value;

    if (CONFIG_FALSE == config_lookup_string (&config, name, &value))
        fprintf(stderr, "%s\n", config_error_text(&config));

    return value;
}

/**
 * @brief Terminate config_t structure.
 * @param config The config_t structure whose memory is to be deallocated.
 *        The structure itself is not deallocated.
 * @ingroup Config
 */
void configTerminate(config_t config)
{
    config_destroy(&config);
}
