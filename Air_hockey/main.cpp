#include <iostream>
#include<cmath>
#include <algorithm>
#include <SDL.h>
#include<SDL_image.h>
#include <SDL_mixer.h>
#include "defs.h"
#include "graphics.h"
#include "logic.h"
#include "game.h"
using namespace std;


int main(int argc, char *argv[])
{
    Game game;
    game.game_start();
    return 0;
}

