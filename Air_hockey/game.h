#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

struct Game{
    Graphics graphics;
    Bat bat;
    Disk disk;
    Bot bot;
    int time_left = INITIAL_TIME;
    int player_score = 0;
    int bot_score = 0;
    int volume = DEFAULT_VOLUME;
    bool music_mute = 1;
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
    void score_and_time(const double& minutes, const int& seconds){
        TTF_Font* font = graphics.loadFont("font\\PixeloidMono-d94EV.ttf", BOARD_FONT_SIZE);

        SDL_Texture* pscore_screen = graphics.renderText(int_to_pchar(player_score), font, WHITE);
        graphics.renderTexture(pscore_screen, SCORE_X, BOT_SCORE_Y);

        SDL_Texture* bscore_screen = graphics.renderText(int_to_pchar(bot_score), font, WHITE);
        graphics.renderTexture(bscore_screen, SCORE_X, PLAYER_SCORE_Y);

        double tempMin = time_left / 60.0 , tempSec = time_left % 60;
        SDL_Texture* seconds_screen = graphics.renderText(int_to_pchar(int(tempSec + 60 - seconds) % 60), font, WHITE);
        graphics.renderTexture(seconds_screen, SECOND_X, TIMER_Y);
        SDL_Texture* minutes_screen = graphics.renderText(int_to_pchar(int(tempMin - minutes)), font, WHITE);
        graphics.renderTexture(minutes_screen, MINUTE_X, TIMER_Y);

        SDL_DestroyTexture(pscore_screen);
        SDL_DestroyTexture(bscore_screen);
        SDL_DestroyTexture(minutes_screen);
        SDL_DestroyTexture(seconds_screen);

        TTF_CloseFont( font );
        pscore_screen = NULL;
        bscore_screen = NULL;
        minutes_screen = NULL;
    }
    void destroy_image(SDL_Texture** a) {
        if (*a != NULL) {
            SDL_DestroyTexture(*a);
            *a = NULL;
        }
    }
    void menu(){
        bool quit_menu=false;
        SDL_Event event;
        int mouse_x , mouse_y;
        TTF_Font* font = graphics.loadFont("font\\PixeloidMono-d94EV.ttf", MENU_TEXT_SIZE);
        SDL_Texture* menu_background = graphics.loadTexture("image\\random.png");
        SDL_Texture* button_image = graphics.loadTexture("image\\button.png");
        SDL_Texture* button_image_pressed = graphics.loadTexture("image\\32x13.png");
        SDL_Texture* play_button = graphics.renderText(PLAY_BUTTON, font, WHITE);
        SDL_Texture* exit_button = graphics.renderText(EXIT_BUTTON, font, WHITE);
        SDL_Texture* setting_button = graphics.renderText(SETTING_BUTTON, font, WHITE);
        while (!quit_menu) {
            graphics.prepareScene();
            graphics.renderTexture(menu_background, 0, 0,900,900);
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) quit_menu = true;
            }
            SDL_GetMouseState(&mouse_x, &mouse_y);

            if (mouse_x >= BUTTON_X && mouse_y >=PLAY_BUTTON_WINDOW_Y && mouse_x <= BUTTON_X + MENU_BUTTON_SIZE && mouse_y <= PLAY_BUTTON_WINDOW_Y + MENU_BUTTON_SIZE_Y){
                graphics.renderTexture(button_image_pressed, BUTTON_X, PLAY_BUTTON_WINDOW_Y, MENU_BUTTON_SIZE, MENU_BUTTON_SIZE);
                graphics.renderTexture(button_image, BUTTON_X, SETTING_BUTTON_WINDOW_Y, MENU_BUTTON_SIZE, MENU_BUTTON_SIZE);
                graphics.renderTexture(button_image, BUTTON_X, EXIT_BUTTON_WINDOW_Y, MENU_BUTTON_SIZE, MENU_BUTTON_SIZE);
            }
            else if(mouse_x >= BUTTON_X && mouse_y >=EXIT_BUTTON_WINDOW_Y && mouse_x <= BUTTON_X + MENU_BUTTON_SIZE && mouse_y <= EXIT_BUTTON_WINDOW_Y + MENU_BUTTON_SIZE_Y){
                graphics.renderTexture(button_image, BUTTON_X, PLAY_BUTTON_WINDOW_Y, MENU_BUTTON_SIZE, MENU_BUTTON_SIZE);
                graphics.renderTexture(button_image, BUTTON_X, SETTING_BUTTON_WINDOW_Y, MENU_BUTTON_SIZE, MENU_BUTTON_SIZE);
                graphics.renderTexture(button_image_pressed, BUTTON_X, EXIT_BUTTON_WINDOW_Y, MENU_BUTTON_SIZE, MENU_BUTTON_SIZE);
            }
            else {
                graphics.renderTexture(button_image, BUTTON_X, PLAY_BUTTON_WINDOW_Y, MENU_BUTTON_SIZE, MENU_BUTTON_SIZE);
                graphics.renderTexture(button_image, BUTTON_X, SETTING_BUTTON_WINDOW_Y, MENU_BUTTON_SIZE, MENU_BUTTON_SIZE);
                graphics.renderTexture(button_image, BUTTON_X, EXIT_BUTTON_WINDOW_Y, MENU_BUTTON_SIZE, MENU_BUTTON_SIZE);
            }
            graphics.renderTexture(play_button, MENU_TEXT_X, PLAY_BUTTON_Y);
            graphics.renderTexture(setting_button, MENU_TEXT_X, SETTING_BUTTON_Y);
            graphics.renderTexture(exit_button, MENU_TEXT_X, EXIT_BUTTON_Y);
            SDL_Delay(10);
            graphics.presentScene();
            SDL_PollEvent(&event);
            switch (event.type) {
                case SDL_QUIT:
                    quit_menu = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (mouse_x >= BUTTON_X && mouse_y >=PLAY_BUTTON_WINDOW_Y && mouse_x <= BUTTON_X + MENU_BUTTON_SIZE && mouse_y <= PLAY_BUTTON_WINDOW_Y + MENU_BUTTON_SIZE_Y){
                        destroy_image(&play_button);
                        destroy_image(&exit_button);
                        destroy_image(&setting_button);
                        destroy_image(&button_image);
                        destroy_image(&button_image_pressed);
                        destroy_image(&menu_background);
                        TTF_CloseFont( font );
                        game_start();
                        return;
                    }
                    if (mouse_x >= BUTTON_X && mouse_y >=EXIT_BUTTON_WINDOW_Y && mouse_x <= BUTTON_X + MENU_BUTTON_SIZE && mouse_y <= EXIT_BUTTON_WINDOW_Y + MENU_BUTTON_SIZE_Y){
                        destroy_image(&play_button);
                        destroy_image(&exit_button);
                        destroy_image(&setting_button);
                        destroy_image(&button_image);
                        destroy_image(&button_image_pressed);
                        destroy_image(&menu_background);
                        TTF_CloseFont( font );
                        return;
                    }
                    break;
            }
        }
        destroy_image(&play_button);
        destroy_image(&exit_button);
        destroy_image(&setting_button);
        destroy_image(&button_image);
        destroy_image(&button_image_pressed);
        destroy_image(&menu_background);
        TTF_CloseFont( font );
    }
    void setting(Mix_Music* gMusic){

    }
    void game_start(){
        SDL_Texture* board_image = graphics.loadTexture("image\\board.png");
        SDL_Texture* player_bat_image = graphics.loadTexture("image\\player_bat.png");
        SDL_Texture* bot_bat_image = graphics.loadTexture("image\\bot_image.png");
        SDL_Texture* disk_image = graphics.loadTexture("image\\disk.png");
        Uint32 startTime = SDL_GetTicks();
        initial_pos();
        disk_initial_pos();
        bool quit = false;
        SDL_Event event;
        while (!quit) {
            graphics.prepareScene();
            SDL_RenderCopy(graphics.renderer, board_image, NULL, NULL);
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) quit = true;
            }
            Uint32 currentTime = SDL_GetTicks();
            Uint32 passedTime = currentTime - startTime;
            double minutes = (passedTime / 1000) / 60.0;
            int seconds = (passedTime / 1000) % 60;
            score_and_time(minutes, seconds);
            bat.batMove();
            disk.movement(bat,bot);
            behavior(bot,disk);
            graphics.renderTexture(player_bat_image, bat.x - BAT_RADIUS, bat.y - BAT_RADIUS, BAT_RADIUS * 2,BAT_RADIUS * 2);
            graphics.renderTexture(bot_bat_image, bot.x - BAT_RADIUS, bot.y - BAT_RADIUS, BAT_RADIUS * 2,BAT_RADIUS * 2);
            graphics.renderTexture(disk_image, disk.x - DISK_RADIUS, disk.y - DISK_RADIUS, DISK_RADIUS * 2,DISK_RADIUS * 2);
            if (disk.player_win) {
                player_won();
            }
            else if (disk.bot_win) {
                bot_won();
            }
            if (bot_score==WIN_POINT||player_score==WIN_POINT)quit = true;
            const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
            if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {
                time_left -= seconds;
                destroy_image(&board_image);
                destroy_image(&player_bat_image);
                destroy_image(&bot_bat_image);
                destroy_image(&disk_image);
                menu();
                return;
            }
            graphics.presentScene();
            SDL_Delay(10);
        }
        destroy_image(&board_image);
        destroy_image(&player_bat_image);
        destroy_image(&bot_bat_image);
        destroy_image(&disk_image   );
    }
    void game_play(){
        graphics.init();
        Mix_Music *gMusic = graphics.loadMusic("music_and_sound\\Phoenix Wright_ Trials and Tribulations OST - Investigation  Middle Stage 2004.mp3");
        graphics.play(gMusic);
        graphics.setMusicVolume(volume);
        menu();
        if (gMusic != nullptr) Mix_FreeMusic( gMusic );
        graphics.quit();
    }
};

#endif // GAME_H_INCLUDED
