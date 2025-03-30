#include <iostream>
#include<bits/stdc++.h>
#include<cmath>
#include <algorithm>
#include<chrono>
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
    Bat bat;
    bat.x = SCREEN_WIDTH / 2;
    bat.y = SCREEN_HEIGHT / 4*3;

    Disk disk;
    disk.x = SCREEN_WIDTH / 2+0.05;
    disk.y = SCREEN_HEIGHT / 2;

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        graphics.prepareScene();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }
        SDL_SetRenderDrawColor(graphics.renderer, 0, 255, 255, 255);
        SDL_RenderDrawLine(graphics.renderer,0,SCREEN_HEIGHT/2,SCREEN_WIDTH,SCREEN_HEIGHT/2);
        moveimage(bat,graphics);
        disk.movement(bat,graphics);
        graphics.presentScene();
        SDL_Delay(10);
    }

    graphics.quit();
    return 0;
}

