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
    // Initialise configuration file.
    config_t config;
    config = configInit(config, NULL);

    // Initialise window.
    uint16_t screenWidth      = configGetInt(config, "video.width");
    uint16_t screenHeight     = configGetInt(config, "video.height");
    uint8_t  screenFullscreen = configGetBool(config, "video.fullscreen");

    const char *title = configGetString(config, "game.title");

    SDL_Surface *screen;
    screen = screenInit(
        screenWidth,
        screenHeight,
        screenFullscreen,
        title);
    if (NULL == screen) return EXIT_FAILURE;

    // Initialise input handler.
    input *controls = inputInit();
    if (NULL == controls) return EXIT_FAILURE;

    // Initialise player entity.
    player *hero = playerInit(config);
    if (NULL == hero) return EXIT_FAILURE;

    // Initialise audio.
    mixer *mix = mixerInit();
    music *tune = musicInit();
    /* Note: The error handling isn't missing.  There is simply no need to quit
     * the program if the music can't be played by some reason. */
    if (NULL != mix)
        if (configGetBool(config, "audio.enabled"))
            musicFadeIn(tune, 5000);

    // Main game loop.
    uint8_t gameIsRunning = 1;
    puts("LCTRL+q to quit.");

    while(gameIsRunning)
    {
        inputGetKeys(controls);

        int8_t plru = playerUpdate(
            screen,
            controls->keyState,
            controls->quit,
            screenWidth,
            screenHeight,
            hero);

        switch(plru)
        {
            case -1: return EXIT_FAILURE;
            case -2: gameIsRunning = 0;
        }
    }

    // Cleanup.
    if (configGetBool(config, "audio.enabled"))
    {
        musicTerminate(tune);
        mixerTerminate(mix);
    }
    playerTerminate(hero);
    inputTerminate(controls);
    screenTerminate();
    configTerminate(config);

    return EXIT_SUCCESS;
}
