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

    Input *input = inputInit();
    if (NULL == input) return EXIT_FAILURE;

    Player *player = playerInit(config);
    if (NULL == player) return EXIT_FAILURE;

    Mixer *mixer = mixerInit();
    Music *music = musicInit();
    /* Note: The error handling isn't missing.  There is simply no need to quit
     * the program if the music can't be played by some reason. */
    if (NULL != mixer)
        if (configGetBool(config, "audio.enabled"))
            musicFadeIn(music, 5000);

    // Main loop.
    uint8_t gameIsRunning = 1;
    while(gameIsRunning)
    {
        gameIsRunning = inputGetKeys(input);
        gameIsRunning = playerUpdate(player, config, input->keyState);
        render(screen, player);
    }

    // Cleanup.
    musicTerminate(music);
    mixerTerminate(mixer);
    playerTerminate(player);
    inputTerminate(input);
    screenTerminate(screen);
    configTerminate(config);

    return EXIT_SUCCESS;
}
