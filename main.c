/** @file main.c
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "main.h"

/**
 * @brief  Main program.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main()
{
    // Initialisation.
    config_t config;
    config = configInit(config, NULL);

    uint16_t   width      = configGetInt(config,    "video.width");
    uint16_t   height     = configGetInt(config,    "video.height");
    uint8_t    fullscreen = configGetBool(config,   "video.fullscreen");
    const char *title     = configGetString(config, "game.title");

    SDL_Surface *screen;
    screen = screenInit(width, height, fullscreen, title);
    if (NULL == screen) return EXIT_FAILURE;

    input *controls = inputInit();
    if (NULL == controls) return EXIT_FAILURE;

    player *hero = playerInit(config);
    if (NULL == hero) return EXIT_FAILURE;

    mixer *mix = mixerInit();
    music *tune = musicInit();
    /* Note: The error handling isn't missing.  There is simply no need to quit
     * the program if the music can't be played by some reason. */
    if (NULL != mix)
        if (configGetBool(config, "audio.enabled"))
            musicFadeIn(tune, 5000);

    // Main loop.
    uint8_t gameIsRunning = 1;
    while(gameIsRunning)
    {
        gameIsRunning = inputGetKeys(controls);
        gameIsRunning = playerUpdate(hero, config, controls->keyState);
        render(screen, hero);
    }

    // Cleanup.
    musicTerminate(tune);
    mixerTerminate(mix);
    playerTerminate(hero);
    inputTerminate(controls);
    screenTerminate();
    configTerminate(config);

    return EXIT_SUCCESS;
}
