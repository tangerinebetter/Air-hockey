#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

const int SCREEN_WIDTH = 900;
const int BOARD_WIDTH = 492;
const int SCREEN_HEIGHT = 900;
const int GOAL_X1 = BOARD_WIDTH/3;
const int GOAL_X2 = BOARD_WIDTH*2/3;
const int BOARD_FONT_SIZE = 100;
const int TIMER_Y = 200;
const int MINUTE_X = 570;
const int SECOND_X = 670;
const int SCORE_X = 650;
const int PLAYER_SCORE_Y = 500;
const int BOT_SCORE_Y = 720;
const int GOAL_PLAYER_Y= 0;
const int GOAL_BOT_Y = SCREEN_HEIGHT;
const int BUTTON_X = 200;
const int MENU_TEXT_X = 250;
const int PLAY_BUTTON_Y = 200;
const int PLAY_BUTTON_WINDOW_Y = PLAY_BUTTON_Y - 50;
const int EXIT_BUTTON_Y = 600;
const int EXIT_BUTTON_WINDOW_Y = EXIT_BUTTON_Y - 50;
const int SETTING_BUTTON_Y = 400;
const int SETTING_BUTTON_WINDOW_Y = SETTING_BUTTON_Y - 50;
const int PAUSE_X = 800;
const int PAUSE_Y = 20;
const int LEFT_ARROW_X = 200;
const int RIGHT_ARROW_X = 500;
const int MUSIC_Y = 100;
const int MUSIC_X = 20;
const int SOUND_Y = 300;
const int SOUND_X = 20;
const int MUSIC_VOLUME_X = 350;
const int SOUND_VOLUME_X = 350;
const int MENU_BUTTON_SIZE = 450;
const int MENU_BUTTON_SIZE_Y = 183;
const int WIN_POINT = 5;
const int MENU_TEXT_SIZE = 70;
const int SETTING_TEXT_SIZE = 75;
const int VOLUME_ICON_SIZE = 150;
const int SETTING_ICON_SIZE = 80;
const int DEFAULT_VOLUME = 30;
const SDL_Color WHITE = {255, 255, 255, 0};
const char* PLAY_BUTTON = "PLAY";
const char* EXIT_BUTTON = "EXIT";
const char* SETTING_BUTTON = "SETTING";
const char* WINDOW_TITLE = "Air Hockey";
const int INITIAL_TIME = 180;
const double NORMAL_SPEED = 8;
const double BAT_RADIUS = 25;
const double DISK_RADIUS = 20;
const double MAX_DISK_SPEED = 10;
const double DECCELERATION = 0.99;
const double MINIMUM_DISK_SPEED = 0.2;
const double START_POS_PLAYER_X = BOARD_WIDTH / 2;
const double START_POS_PLAYER_Y = SCREEN_HEIGHT / 8*7;
const double START_POS_BOT_Y = SCREEN_HEIGHT / 8;
const double START_POS_DISK_X = BOARD_WIDTH / 2+0.05;
const double START_POS_DISK_Y = SCREEN_HEIGHT / 2;
const int BOT_WON_Y = SCREEN_HEIGHT/4*3;
const int PLAYER_WON_Y = SCREEN_HEIGHT/4;


#endif // DEFS_H_INCLUDED
