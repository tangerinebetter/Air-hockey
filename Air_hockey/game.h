#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

struct Game{
    Graphics graphics;
    Bat bat;
    Disk disk;
    Bot bot;
    int player_score = 0, bot_score = 0;
    void initial_pos(){
        bat.x = START_POS_PLAYER_X;
        bat.y = START_POS_PLAYER_Y;
        bot.x = START_POS_PLAYER_X;
        bot.y = START_POS_BOT_Y;
    }
    void disk_initial_pos(){
        disk.x = START_POS_DISK_X;
        disk.y = START_POS_DISK_Y;
    }
    void player_won(){
        initial_pos();
        disk.x = START_POS_DISK_X;
        disk.y = START_POS_DISK_Y+ SCREEN_HEIGHT/3;
        disk.player_win = 0;
        disk.dx=0;
        disk.dy=0;
        player_score++;
    }
    void bot_won(){
        initial_pos();
        disk.x = START_POS_DISK_X;
        disk.y = START_POS_DISK_Y - SCREEN_HEIGHT/3;
        disk.bot_win = 0;
        disk.dx=0;
        disk.dy=0;
        bot_score++;
    }
    void game_start(){
        graphics.init();
        Mix_Music *gMusic = graphics.loadMusic("music_and_sound\\Phoenix Wright_ Trials and Tribulations OST - Investigation  Middle Stage 2004.mp3");
        graphics.play(gMusic);
        graphics.setMusicVolume(20);
        initial_pos();
        disk_initial_pos();
        bool quit = false;
        SDL_Event event;
        while (!quit) {
            graphics.prepareScene();
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) quit = true;
            }
            SDL_SetRenderDrawColor(graphics.renderer, 0, 255, 255, 255);//tam
            SDL_RenderDrawLine(graphics.renderer,0,SCREEN_HEIGHT/2,BOARD_WIDTH,SCREEN_HEIGHT/2);//tam
            SDL_RenderDrawLine(graphics.renderer,BOARD_WIDTH,0,BOARD_WIDTH,SCREEN_HEIGHT);//tam
            bat.batMove(graphics);
            disk.movement(bat,bot,graphics);
            if (disk.player_win) {
                player_won();
            }
            else if (disk.bot_win) {
                bot_won();
            }
            if (bot_score==5||player_score==5)quit = true;
            behavior(bot,disk,graphics);
            graphics.presentScene();
            SDL_Delay(10);
        }
        if (gMusic != nullptr) Mix_FreeMusic( gMusic );
        graphics.quit();
    }
};

#endif // GAME_H_INCLUDED
