#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

struct Game{
    Graphics graphics;
    Bat bat;
    Disk disk;
    Bot bot;
    int player_score = 0;
    int bot_score = 0;
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
    char *int_to_pchar(const int& a){
        std::string s = std::to_string(a);
        int sl=s.length();
        char *ps= new char[sl+1];
        strcpy(ps, s.c_str());
        return ps;
    }
    void score_and_time(const double& minutes, const double& seconds){
        TTF_Font* font = graphics.loadFont("font\\PixeloidMono-d94EV.ttf", 100);
        SDL_Color color = {255, 255, 255, 0};

        SDL_Texture* pscore_screen = graphics.renderText(int_to_pchar(player_score), font, color);
        graphics.renderTexture(pscore_screen, 500, 200);

        SDL_Texture* bscore_screen = graphics.renderText(int_to_pchar(bot_score), font, color);
        graphics.renderTexture(bscore_screen, 600, 200);

        double tempMin = 5 , tempSec = 0;
        SDL_Texture* seconds_screen = graphics.renderText(int_to_pchar(int(tempSec + 60 - seconds) % 60), font, color);
        graphics.renderTexture(seconds_screen, 600, 100);
        SDL_Texture* minutes_screen = graphics.renderText(int_to_pchar(int(tempMin - minutes)), font, color);
        graphics.renderTexture(minutes_screen, 500, 100);

        SDL_DestroyTexture(pscore_screen);
        SDL_DestroyTexture(bscore_screen);
        SDL_DestroyTexture(minutes_screen);
        SDL_DestroyTexture(seconds_screen);

        TTF_CloseFont( font );
        pscore_screen = NULL;
        bscore_screen = NULL;
        minutes_screen = NULL;
    }
    void menu(){
        Mix_Music *gMusic = graphics.loadMusic("music_and_sound\\Phoenix Wright_ Trials and Tribulations OST - Investigation  Middle Stage 2004.mp3");
        graphics.play(gMusic);
        graphics.setMusicVolume(20);
        bool quit_menu=false;
        SDL_Event event;
        while (!quit_menu) {
            graphics.prepareScene();
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) quit_menu = true;
            }
            TTF_Font* font = graphics.loadFont("font\\PixeloidMono-d94EV.ttf", 100);
            SDL_Color color = {255, 255, 255, 0};
            SDL_Texture* play_button = graphics.renderText(PLAY_BUTTON, font, color);
            graphics.renderTexture(play_button, 200, 200);
            SDL_DestroyTexture(play_button);
            TTF_CloseFont( font );
            play_button = NULL;
            graphics.presentScene();
            const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
            if (currentKeyStates[SDL_SCANCODE_UP]) {
                game_start();
                if (gMusic != nullptr) Mix_FreeMusic( gMusic );
                return;
            }
            SDL_Delay(10);
        }
        if (gMusic != nullptr) Mix_FreeMusic( gMusic );
    }
    void game_play(){
        graphics.init();
        menu();
        graphics.quit();
    }
    void game_start(){
        Uint32 startTime = SDL_GetTicks();
        initial_pos();
        disk_initial_pos();
        bool quit = false;
        SDL_Event event;
        while (!quit) {
            graphics.prepareScene();
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) quit = true;
            }
            Uint32 currentTime = SDL_GetTicks();
            Uint32 passedTime = currentTime - startTime;
            double minutes = (passedTime / 1000.0) / 60.0;
            double seconds = (passedTime / 1000) % 60;
            score_and_time(minutes,seconds);
            SDL_SetRenderDrawColor(graphics.renderer, 0, 255, 255, 255);//tam
            SDL_RenderDrawLine(graphics.renderer, 0, SCREEN_HEIGHT/2, BOARD_WIDTH, SCREEN_HEIGHT/2);//tam
            SDL_RenderDrawLine(graphics.renderer,BOARD_WIDTH,0,BOARD_WIDTH,SCREEN_HEIGHT);//tam
            bat.batMove(graphics);
            disk.movement(bat,bot,graphics);
            if (disk.player_win) {
                player_won();
            }
            else if (disk.bot_win) {
                bot_won();
            }
            if (bot_score==WIN_POINT||player_score==WIN_POINT)quit = true;
            behavior(bot,disk,graphics);
            const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
            if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {
                menu();
                return;
            }
            graphics.presentScene();
            SDL_Delay(10);
        }
    }
};

#endif // GAME_H_INCLUDED
