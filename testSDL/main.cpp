#include <iostream>
#include <SDL.h>
#include<SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "logic.h"
using namespace std;



int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();
    Mouse mouse;
    mouse.x = SCREEN_WIDTH / 2;
    mouse.y = SCREEN_HEIGHT / 2;

    bool quit = false;
    SDL_Event event;
    while (!quit && !gameOver(mouse)) {
        graphics.prepareScene();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }
        moveimage(mouse,graphics);

        graphics.presentScene();
        SDL_Delay(10);
    }


    graphics.quit();
    return 0;
}

