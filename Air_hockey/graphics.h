#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include <SDL_mixer.h>


struct Graphics {
    SDL_Renderer *renderer;
    SDL_Window *window;

    void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "%s: %s", msg, error);
        SDL_Quit();
    }

    void init() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                   SDL_WINDOW_SHOWN);
        if (window == nullptr)
                   logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1,
                     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        //renderer =
                  SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr)
             logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
           logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",Mix_GetError() );
        }
        if (TTF_Init() == -1) {
            logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ",
                             TTF_GetError());
        }

    }
    Mix_Music *loadMusic(const char* path)
    {
        Mix_Music *gMusic = Mix_LoadMUS(path);
        if (gMusic == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                "Could not load music! SDL_mixer Error: %s", Mix_GetError());
        }
        return gMusic;
    }
    void play(Mix_Music *gMusic)
    {
        if (gMusic == nullptr) return;

        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic( gMusic, -1 );
        }
        else if( Mix_PausedMusic() == 1 ) {
            Mix_ResumeMusic();
        }
    }
    Mix_Chunk* loadSound(const char* path) {
        Mix_Chunk* gChunk = Mix_LoadWAV(path);
        if (gChunk == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
               "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
        }
        return gChunk;
    }
    void play(Mix_Chunk* gChunk) {
        if (gChunk != nullptr) {
            Mix_PlayChannel( -1, gChunk, 0 );
        }
    }
    void pauseMusic() {
        if (Mix_PlayingMusic() == 1) {
            Mix_PauseMusic();
        }
    }
    void resumeMusic(){
        Mix_ResumeMusic();
    }
    void stopMusic() {
        Mix_HaltMusic();
    }
    void setMusicVolume(int volume) {
        if (volume >= 0 && volume <= 128) {
            Mix_VolumeMusic(volume);
        } else {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                           "Invalid music volume: %d. Volume should be between 0 and 128.", volume);
        }
    }
    void setSoundVolume(Mix_Chunk* gChunk,int volume) {
        if (volume >= 0 && volume <= 128) {
            Mix_VolumeChunk(gChunk,volume);
        } else {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                           "Invalid sound volume: %d. Volume should be between 0 and 128.", volume);
        }
    }
    void prepareScene()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

	void prepareScene(SDL_Texture * background)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy( renderer, background, NULL, NULL);
    }

    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }

    SDL_Texture *loadTexture(const char *filename)
    {
        //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,"Loading %s", filename);
        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                  SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }


    void renderTexture(SDL_Texture *texture, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }
    void renderTexture(SDL_Texture *texture, int x, int y, int width, int height)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w = width;
        dest.h = height;

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }
    void renderTexture(SDL_Texture *texture, int x, int y, int width, int height, Uint8 alpha) {
        SDL_Rect dest;
        dest.x = x;
        dest.y = y;
        dest.w = width;
        dest.h = height;
        SDL_SetTextureAlphaMod(texture, alpha);
        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }
    void renderTexture(SDL_Texture *texture, int x, int y, Uint8 alpha) {
        SDL_Rect dest;
        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        SDL_SetTextureAlphaMod(texture, alpha);
        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    TTF_Font* loadFont(const char* path, int size)
    {
        TTF_Font* gFont = TTF_OpenFont( path, size );
        if (gFont == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"Load font %s", TTF_GetError());
        }
        return gFont;
    }
    SDL_Texture* renderText(const char* text,TTF_Font* font, SDL_Color textColor)
    {
        SDL_Surface* textSurface =
                TTF_RenderText_Solid( font, text, textColor );
        if( textSurface == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Render text surface %s", TTF_GetError());
            return nullptr;
        }

        SDL_Texture* texture =
                SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Create texture from text %s", SDL_GetError());
        }
        SDL_FreeSurface( textSurface );
        return texture;
    }

    void quit()
    {
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

#endif // GRAPHICS_H_INCLUDED
