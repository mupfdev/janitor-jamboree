/** @file config.c
 * @ingroup   Config
 * @defgroup  Config
 * @brief     Configuration file handler.
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "config.h"

/**
 * @brief   
 * @param   config
 * @param   filename
 * @return  
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
 * @brief   
 * @param   config
 * @param   name
 * @return  
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
 * @brief   
 * @param   config
 * @param   name
 * @return  
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
 * @brief   
 * @param   config
 * @param   name
 * @return  
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
 * @brief   
 * @param   config
 * @ingroup Config
 */
void configTerminate(config_t config)
{
    config_destroy(&config);
}
