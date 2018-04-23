/** @file main.c
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 * @todo      Add configuration handler and source documentation!
 */

#include "main.h"

/**
 * @brief  Main program.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on error.
 */
int main()
{
    Screen *screen;
    screen = screenInit();
    if (NULL == screen) return EXIT_FAILURE;

    atexit(SDL_Quit);

    Renderer *renderer;
    renderer = rendererInit(screen);
    if (NULL == renderer) return EXIT_FAILURE;

    Input *input = inputInit();
    if (NULL == input) return EXIT_FAILURE;

    Map *map = mapInit();
    if (NULL == map) return EXIT_FAILURE;
    map->filename = "res/maps/outskirts.tmx";
    if (-1 == mapLoadTmx(map)) return EXIT_FAILURE;
    //if (-1 == renderMap(renderer, map)) return EXIT_FAILURE;

    Player *player = playerInit();
    if (NULL == player) return EXIT_FAILURE;
    player->filename = "res/sprites/male.png";

    /* Note: The error handling isn't missing here.  There is simply no need to
     * quit the program if the music can't be played by some reason. */
    Mixer *mixer    = mixerInit();
    Music *music    = musicInit();
    music->filename = "res/music/overworld theme.ogg";
    if (1 == AUDIO_ENABLED) musicFadeIn(music, 5000);

    while(1)
    {
        if (-1 == inputLoop(input))                           break;
        if (-1 == playerLoop(player, input->keyState))        break;
        if (-1 == renderScene(screen, renderer, player, map)) break;
    }

    musicTerminate(music);
    mixerTerminate(mixer);
    playerTerminate(player);
    mapTerminate(map);
    inputTerminate(input);
    rendererTerminate(renderer);
    screenTerminate(screen);

    return EXIT_SUCCESS;
}
