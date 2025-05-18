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
    int music_volume = DEFAULT_VOLUME;
    int sound_volume = DEFAULT_VOLUME;
    std::deque<int> trace_x;
    std::deque<int> trace_y;
    bool mMute = 0;
    bool sMute = 0;
    bool hard = 1;
    void initial_pos(){
        bat.x = START_POS_PLAYER_X;
        bat.y = START_POS_PLAYER_Y;
        bot.x = START_POS_PLAYER_X;
        bot.y = START_POS_BOT_Y;
        disk.x = START_POS_DISK_X;
        disk.y = START_POS_DISK_Y;
        disk.dx=0;
        disk.dy=0;
    }
    void player_won(){
        initial_pos();
        disk.player_win = 0;
        player_score++;
    }
    void bot_won(){
        initial_pos();
        disk.bot_win = 0;
        bot_score++;
    }
    char *int_to_pchar(const int& a){
        std::string s = std::to_string(a);
        int sl=s.length();
        char *ps= new char[sl+1];
        strcpy(ps, s.c_str());
        return ps;
    }
    void rendertrace(SDL_Texture* image){
        if (trace_x.size() < TRACE_LENGTH && trace_y.size() < TRACE_LENGTH){
            trace_x.push_back(disk.x);
            trace_y.push_back(disk.y);
        }
        else {
            trace_x.push_back(disk.x);
            trace_y.push_back(disk.y);
            trace_x.pop_front();
            trace_y.pop_front();
        }
        int temp = trace_x.size();
        for (int i=0;i<temp;++i){
            graphics.renderTexture(image, trace_x[i] - DISK_RADIUS, trace_y[i] - DISK_RADIUS, DISK_RADIUS * 2,DISK_RADIUS * 2,50);
        }
    }
    void destroy_image(SDL_Texture** a) {
        if (*a != NULL) {
            SDL_DestroyTexture(*a);
            *a = NULL;
        }
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

        destroy_image(&pscore_screen);
        destroy_image(&bscore_screen);
        destroy_image(&minutes_screen);
        destroy_image(&seconds_screen);
        TTF_CloseFont( font );
    }
    void setting(Mix_Music* gMusic, bool& quit){
        bool quit_menu=false;
        bool menu_called = false;
        SDL_Event event;
        int mouse_x , mouse_y;
        TTF_Font* font = graphics.loadFont("font\\PixeloidMono-d94EV.ttf", SETTING_TEXT_SIZE);
        TTF_Font* font2 = graphics.loadFont("font\\PixeloidMono-d94EV.ttf", SETTING_TEXT_SIZE/2);
        SDL_Texture* setting_background = graphics.loadTexture("image\\star.png ");
        SDL_Texture* left_arrow = graphics.loadTexture("image\\left_arrow.png");
        SDL_Texture* right_arrow = graphics.loadTexture("image\\right_arrow.png");
        SDL_Texture* music = graphics.loadTexture("image\\music.png");
        SDL_Texture* music_muted = graphics.loadTexture("image\\music_mute.png");
        SDL_Texture* sound = graphics.loadTexture("image\\sound.png");
        SDL_Texture* sound_muted = graphics.loadTexture("image\\sound_mute.png");
        SDL_Texture* exit = graphics.loadTexture("image\\exit.png");
        SDL_Texture* button_image = graphics.loadTexture("image\\button.png");
        SDL_Texture* button_image_pressed = graphics.loadTexture("image\\32x13.png");
        SDL_Texture* menu_button = graphics.renderText("MENU", font2, WHITE);
        SDL_Texture* hard_difficulty = graphics.renderText("HARD", font2, WHITE);
        SDL_Texture* easy_difficulty = graphics.renderText("EASY", font2, WHITE);
        while (!quit_menu) {
            graphics.prepareScene();
            graphics.renderTexture(setting_background, 0, 0, 900, 900);
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) quit_menu = true;
            }
            SDL_GetMouseState(&mouse_x, &mouse_y);
            graphics.renderTexture(left_arrow, LEFT_ARROW_X, MUSIC_Y, SETTING_ICON_SIZE, SETTING_ICON_SIZE);
            graphics.renderTexture(right_arrow, RIGHT_ARROW_X, MUSIC_Y, SETTING_ICON_SIZE, SETTING_ICON_SIZE);
            graphics.renderTexture(left_arrow, LEFT_ARROW_X, SOUND_Y, SETTING_ICON_SIZE, SETTING_ICON_SIZE);
            graphics.renderTexture(right_arrow, RIGHT_ARROW_X, SOUND_Y, SETTING_ICON_SIZE, SETTING_ICON_SIZE);
            graphics.renderTexture((mMute ? music_muted : music), MUSIC_X, MUSIC_Y, VOLUME_ICON_SIZE, VOLUME_ICON_SIZE);
            graphics.renderTexture((sMute? sound_muted : sound), SOUND_X, SOUND_Y, VOLUME_ICON_SIZE, VOLUME_ICON_SIZE);
            graphics.renderTexture(exit, PAUSE_X, PAUSE_Y, SETTING_ICON_SIZE, SETTING_ICON_SIZE);
            SDL_Texture* sVolume = graphics.renderText(int_to_pchar(sound_volume), font, WHITE);
            SDL_Texture* mVolume = graphics.renderText(int_to_pchar(music_volume), font, WHITE);
            graphics.renderTexture(mVolume, MUSIC_VOLUME_X, MUSIC_Y);
            graphics.renderTexture(sVolume, SOUND_VOLUME_X, SOUND_Y);
            if (mouse_x >= SETTING_MENU_X && mouse_y >=SETTING_MENU_Y && mouse_x <= SETTING_MENU_X + SETTING_BUTTON_SIZE && mouse_y <= SETTING_MENU_Y + SETTING_BUTTON_SIZE_Y){
                graphics.renderTexture(button_image_pressed, SETTING_MENU_X, SETTING_MENU_Y, SETTING_BUTTON_SIZE, SETTING_BUTTON_SIZE);
                graphics.renderTexture(button_image, SETTING_MENU_X, SETTING_DIFF_Y, SETTING_BUTTON_SIZE, SETTING_BUTTON_SIZE);
            }
            else if (mouse_x >= SETTING_MENU_X && mouse_y >=SETTING_DIFF_Y && mouse_x <= SETTING_MENU_X + SETTING_BUTTON_SIZE && mouse_y <= SETTING_DIFF_Y + SETTING_BUTTON_SIZE_Y){
                graphics.renderTexture(button_image, SETTING_MENU_X, SETTING_MENU_Y, SETTING_BUTTON_SIZE, SETTING_BUTTON_SIZE);
                graphics.renderTexture(button_image_pressed, SETTING_MENU_X, SETTING_DIFF_Y, SETTING_BUTTON_SIZE, SETTING_BUTTON_SIZE);
            }
            else {
                graphics.renderTexture(button_image, SETTING_MENU_X, SETTING_MENU_Y, SETTING_BUTTON_SIZE, SETTING_BUTTON_SIZE);
                graphics.renderTexture(button_image, SETTING_MENU_X, SETTING_DIFF_Y, SETTING_BUTTON_SIZE, SETTING_BUTTON_SIZE);
            }
            graphics.renderTexture(menu_button, SETTING_MENU_TEXT_X, SETTING_MENU_TEXT_Y);
            graphics.renderTexture(hard?hard_difficulty:easy_difficulty, SETTING_MENU_TEXT_X, SETTING_DIFF_TEXT_Y);
            destroy_image(&mVolume);
            destroy_image(&sVolume);
            SDL_Delay(10);
            graphics.presentScene();
            SDL_PollEvent(&event);
            switch (event.type) {
                case SDL_QUIT:
                    quit_menu = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (mouse_x >= PAUSE_X && mouse_y >= PAUSE_Y && mouse_x <= PAUSE_X + SETTING_ICON_SIZE && mouse_y <= PAUSE_Y + SETTING_ICON_SIZE){
                        quit_menu = true;
                        break;
                    }
                    if (mouse_x >= LEFT_ARROW_X && mouse_y >= MUSIC_Y && mouse_x <= LEFT_ARROW_X + SETTING_ICON_SIZE && mouse_y <= MUSIC_Y + SETTING_ICON_SIZE){
                        if (music_volume > 0){
                            music_volume -= 5;
                            graphics.setMusicVolume(music_volume);
                        }
                    }
                    if (mouse_x >= RIGHT_ARROW_X && mouse_y >= MUSIC_Y && mouse_x <= RIGHT_ARROW_X + SETTING_ICON_SIZE && mouse_y <= MUSIC_Y + SETTING_ICON_SIZE){
                        if(music_volume < 100){
                            music_volume += 5;
                            graphics.setMusicVolume(music_volume);
                        }
                    }
                    if (mouse_x >= LEFT_ARROW_X && mouse_y >= SOUND_Y && mouse_x <= LEFT_ARROW_X + SETTING_ICON_SIZE && mouse_y <= SOUND_Y + SETTING_ICON_SIZE){
                        if (sound_volume > 0){
                            sound_volume -= 5;
                        }
                    }
                    if (mouse_x >= RIGHT_ARROW_X && mouse_y >= SOUND_Y && mouse_x <= RIGHT_ARROW_X + SETTING_ICON_SIZE && mouse_y <= SOUND_Y + SETTING_ICON_SIZE){
                        if(sound_volume < 100){
                            sound_volume += 5;
                        }
                    }
                    if (mouse_x >= MUSIC_X && mouse_y >= MUSIC_Y && mouse_x <= MUSIC_X + VOLUME_ICON_SIZE && mouse_y <= MUSIC_Y + VOLUME_ICON_SIZE){
                        if (mMute){
                            mMute = false;
                            graphics.resumeMusic();
                        }
                        else {
                            mMute = true;
                            graphics.pauseMusic();
                        }
                    }
                    if (mouse_x >= SOUND_X && mouse_y >= SOUND_Y && mouse_x <= SOUND_X + VOLUME_ICON_SIZE && mouse_y <= SOUND_Y + VOLUME_ICON_SIZE){
                        if (sMute){
                            sMute = false;
                        }
                        else {
                            sMute = true;
                        }
                    }
                    if (mouse_x >= SETTING_MENU_X && mouse_y >=SETTING_MENU_Y && mouse_x <= SETTING_MENU_X + SETTING_BUTTON_SIZE && mouse_y <= SETTING_MENU_Y + SETTING_BUTTON_SIZE_Y){
                        menu_called = true;
                        quit_menu = true;
                        quit = true;
                        break;
                    }
                    if (mouse_x >= SETTING_MENU_X && mouse_y >=SETTING_DIFF_Y && mouse_x <= SETTING_MENU_X + SETTING_BUTTON_SIZE && mouse_y <= SETTING_DIFF_Y + SETTING_BUTTON_SIZE_Y){
                        if (hard)hard = false;
                        else hard = true;
                    }
                    break;

            }
        }
        destroy_image(&setting_background);
        destroy_image(&left_arrow);
        destroy_image(&right_arrow);
        destroy_image(&music);
        destroy_image(&music_muted);
        destroy_image(&sound);
        destroy_image(&sound_muted);
        destroy_image(&exit);
        destroy_image(&button_image);
        destroy_image(&button_image_pressed);
        destroy_image(&menu_button);
        TTF_CloseFont( font );
        TTF_CloseFont( font2 );
        if(menu_called) menu(gMusic);
    }
    void menu(Mix_Music* gMusic){
        bool quit_menu=false;
        SDL_Event event;
        int mouse_x , mouse_y;
        TTF_Font* font = graphics.loadFont("font\\PixeloidMono-d94EV.ttf", MENU_TEXT_SIZE);
        SDL_Texture* menu_background = graphics.loadTexture("image\\Starry Night - Vincent Van Gogh. (Cronosart99).png");
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
            else if(mouse_x >= BUTTON_X && mouse_y >=SETTING_BUTTON_WINDOW_Y && mouse_x <= BUTTON_X + MENU_BUTTON_SIZE && mouse_y <= SETTING_BUTTON_WINDOW_Y + MENU_BUTTON_SIZE_Y){
                graphics.renderTexture(button_image, BUTTON_X, PLAY_BUTTON_WINDOW_Y, MENU_BUTTON_SIZE, MENU_BUTTON_SIZE);
                graphics.renderTexture(button_image_pressed, BUTTON_X, SETTING_BUTTON_WINDOW_Y, MENU_BUTTON_SIZE, MENU_BUTTON_SIZE);
                graphics.renderTexture(button_image, BUTTON_X, EXIT_BUTTON_WINDOW_Y, MENU_BUTTON_SIZE, MENU_BUTTON_SIZE);
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
                        game_start(gMusic);
                        return;
                    }
                    if (mouse_x >= BUTTON_X && mouse_y >=SETTING_BUTTON_WINDOW_Y && mouse_x <= BUTTON_X + MENU_BUTTON_SIZE && mouse_y <= SETTING_BUTTON_WINDOW_Y + MENU_BUTTON_SIZE_Y){
                        setting(gMusic,quit_menu);
                        break;
                    }
                    if (mouse_x >= BUTTON_X && mouse_y >=EXIT_BUTTON_WINDOW_Y && mouse_x <= BUTTON_X + MENU_BUTTON_SIZE && mouse_y <= EXIT_BUTTON_WINDOW_Y + MENU_BUTTON_SIZE_Y){
                        quit_menu = true;
                        break;
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
        return;
    }

    void game_start(Mix_Music* gMusic){
        SDL_Texture* board_image = graphics.loadTexture("image\\board.png");
        SDL_Texture* pause = graphics.loadTexture("image\\pause.png");
        SDL_Texture* player_bat_image = graphics.loadTexture("image\\player_bat.png");
        SDL_Texture* bot_bat_image = graphics.loadTexture("image\\bot_image.png");
        SDL_Texture* disk_image = graphics.loadTexture("image\\disk.png");
        SDL_Texture* disk_image2 = graphics.loadTexture("image\\disk.png");
        SDL_Texture* win_image = graphics.loadTexture("image\\won.png");
        SDL_Texture* lose_image = graphics.loadTexture("image\\lost.png");
        Mix_Chunk* hit_sound = graphics.loadSound("music_and_sound\\retro-select-236670.wav");
        if(!sMute)graphics.setSoundVolume(hit_sound,sound_volume);
        else graphics.setSoundVolume(hit_sound,0);
        Uint32 startTime = SDL_GetTicks();
        Uint32 pausedTime = 0;
        Uint32 counter = 0;
        initial_pos();
        bot.speed = hard?NORMAL_SPEED:NORMAL_SPEED/2;
        bot.diagonalSpeed = bot.speed/sqrt(2);
        bool quit = false;
        int mouse_x , mouse_y;
        SDL_Event event;
        while (!quit) {
            graphics.prepareScene();
            SDL_RenderCopy(graphics.renderer, board_image, NULL, NULL);
            graphics.renderTexture(pause, PAUSE_X, PAUSE_Y, SETTING_ICON_SIZE,SETTING_ICON_SIZE);
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) quit = true;
            }
            Uint32 currentTime = SDL_GetTicks();
            Uint32 passedTime = currentTime - startTime - pausedTime;
            double minutes = (passedTime / 1000) / 60.0;
            int seconds = (passedTime / 1000) % 60;
            score_and_time(minutes, seconds);
            bat.batMove();
            disk.movement(bat,bot,graphics,hit_sound);
            behavior(bot,disk);
            graphics.renderTexture(player_bat_image, bat.x - BAT_RADIUS, bat.y - BAT_RADIUS, BAT_RADIUS * 2,BAT_RADIUS * 2);
            graphics.renderTexture(bot_bat_image, bot.x - BAT_RADIUS, bot.y - BAT_RADIUS, BAT_RADIUS * 2,BAT_RADIUS * 2);
            if (disk.y>SCREEN_HEIGHT/2-50&&disk.y<SCREEN_HEIGHT/2+50) counter = SDL_GetTicks();
            if (currentTime - counter < 5000)rendertrace(disk_image2);
            graphics.renderTexture(disk_image, disk.x - DISK_RADIUS, disk.y - DISK_RADIUS, DISK_RADIUS * 2,DISK_RADIUS * 2);
            if (disk.player_win) {
                player_won();
            }
            else if (disk.bot_win) {
                bot_won();
            }
            if (bot_score==WIN_POINT || player_score==WIN_POINT || (passedTime / 1000) >= INITIAL_TIME){
                graphics.prepareScene();
                if(bot_score > player_score){
                    graphics.renderTexture(lose_image, 0, 0, SCREEN_WIDTH,SCREEN_WIDTH);
                }
                else {
                    graphics.renderTexture(win_image, 0, 0, SCREEN_WIDTH,SCREEN_WIDTH);
                }
                graphics.presentScene();
                SDL_Delay(1000);
                quit = true;
            }
            const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
            if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {
                Uint32 pauseStartTime = SDL_GetTicks();
                setting(gMusic,quit);
                pausedTime += (SDL_GetTicks() - pauseStartTime);
                startTime = SDL_GetTicks() + pausedTime - passedTime;
                if(!sMute)graphics.setSoundVolume(hit_sound,sound_volume);
                else graphics.setSoundVolume(hit_sound,0);
                bot.speed = hard?NORMAL_SPEED:EASY_SPEED;
                bot.diagonalSpeed = bot.speed/sqrt(2);
            }
            graphics.presentScene();
            SDL_Delay(10);
            SDL_GetMouseState(&mouse_x, &mouse_y);
            SDL_PollEvent(&event);
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (mouse_x >= PAUSE_X && mouse_y >= PAUSE_Y && mouse_x <= PAUSE_X + SETTING_ICON_SIZE && mouse_y <= PAUSE_Y + SETTING_ICON_SIZE){
                        Uint32 pauseStartTime = SDL_GetTicks();
                        pausedTime += (SDL_GetTicks() - pauseStartTime);
                        setting(gMusic,quit);
                        startTime = SDL_GetTicks() + pausedTime - passedTime;
                        bot.speed = hard?NORMAL_SPEED:EASY_SPEED;
                        bot.diagonalSpeed = bot.speed/sqrt(2);
                        if(!sMute)graphics.setSoundVolume(hit_sound,sound_volume);
                        else graphics.setSoundVolume(hit_sound,0);
                    }
                    break;
            }
        }
        if (hit_sound != nullptr) Mix_FreeChunk( hit_sound );
        hit_sound = NULL;
        destroy_image(&win_image);
        destroy_image(&lose_image);
        destroy_image(&board_image);
        destroy_image(&player_bat_image);
        destroy_image(&bot_bat_image);
        destroy_image(&disk_image);
        destroy_image(&pause);
    }
    void game_play(){
        graphics.init();
        SDL_SetRenderDrawBlendMode(graphics.renderer, SDL_BLENDMODE_BLEND);
        Mix_Music *gMusic = graphics.loadMusic("music_and_sound\\Phoenix Wright_ Trials and Tribulations OST - Investigation  Middle Stage 2004.mp3");
        graphics.play(gMusic);
        graphics.setMusicVolume(music_volume);
        menu(gMusic);
        if (gMusic != nullptr) Mix_FreeMusic( gMusic );
        gMusic = NULL;
        graphics.quit();
    }
};

#endif // GAME_H_INCLUDED
