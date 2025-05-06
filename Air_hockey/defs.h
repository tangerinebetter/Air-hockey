#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

const int SCREEN_WIDTH = 840;
const int BOARD_WIDTH = 485;
const int SCREEN_HEIGHT = 840;
const int GOAL_X1 = BOARD_WIDTH/3;
const int GOAL_X2 = BOARD_WIDTH*2/3;
const int GOAL_PLAYER_Y= 0;
const int GOAL_BOT_Y = SCREEN_HEIGHT;
const int WIN_POINT = 5;
const char* PLAY_BUTTON = "PLAY";
const char* EXIT_BUTTON = "EXIT";
const char* SETTING_BUTTON = "SETTING";
const char* WINDOW_TITLE = "Air Hockey";
const double NORMAL_SPEED = 8;
const double BAT_RADIUS = 20;
const double DISK_RADIUS = 18;
const double MAX_DISK_SPEED = 10;
const double MINIMUM_DISK_SPEED = 0.2;
const double START_POS_PLAYER_X = BOARD_WIDTH / 2;
const double START_POS_PLAYER_Y = SCREEN_HEIGHT / 4*3;
const double START_POS_BOT_Y = SCREEN_HEIGHT / 4;
const double START_POS_DISK_X = BOARD_WIDTH / 2+0.05;
const double START_POS_DISK_Y = SCREEN_HEIGHT / 2;


#endif // DEFS_H_INCLUDED
