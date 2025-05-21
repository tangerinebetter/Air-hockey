#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

struct Bat {
    double x, y;
    double dx = 0, dy = 0;
    bool moved=false;
    double speed = NORMAL_SPEED * 1.25;
    double diagonalSpeed = speed/sqrt(2);

    void move() {
        x += dx; y += dy;
    }
    void turnNorth() {
        dy = -speed; dx = 0;
    }
    void turnSouth() {
        dy = speed; dx = 0;
    }
    void turnWest() {
        dy = 0; dx = -speed;
    }
    void turnEast() {
        dy = 0; dx = speed;
    }
    void turnNorthEast(){
        dy = -diagonalSpeed; dx = diagonalSpeed;
    }
    void turnNorthWest(){
        dy = -diagonalSpeed; dx = -diagonalSpeed;
    }
    void turnSouthEast(){
        dy = diagonalSpeed; dx = diagonalSpeed;
    }
    void turnSouthWest(){
        dy = diagonalSpeed; dx = -diagonalSpeed;
    }
    void stayStill(){
        dx = 0 ;dy = 0;
    }
    void playRange() {
        if (x - BAT_RADIUS < 0) x = BAT_RADIUS;
        if (x + BAT_RADIUS > BOARD_WIDTH - 1) x = BOARD_WIDTH - BAT_RADIUS;
        if (y - BAT_RADIUS < SCREEN_HEIGHT / 2 - 1) y = SCREEN_HEIGHT / 2 - 1 + BAT_RADIUS;
        if (y + BAT_RADIUS > SCREEN_HEIGHT - 1) y = SCREEN_HEIGHT - 1 - BAT_RADIUS;
    }
    void batMove(){
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        moved=false;

        if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
            turnNorthEast();
            moved = true;
        }

        else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_LEFT]) {
            turnNorthWest();
            moved = true;
        }

        else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
            turnSouthEast();
            moved = true;
        }

        else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_LEFT]) {
            turnSouthWest();
            moved = true;
        }

        else if (currentKeyStates[SDL_SCANCODE_UP]) {
            turnNorth();
            moved = true;
        }
        else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
            turnSouth();
            moved = true;
        }
        else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            turnWest();
            moved = true;
        }
        else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            turnEast();
            moved = true;
        }
        if (moved){
            move();
        }
        else if (!moved){
            stayStill();
        }
        playRange();
    }
};

struct Bot{
    double x, y;
    double dx = 0, dy = 0;
    double speed = NORMAL_SPEED/2;
    double diagonalSpeed = speed/sqrt(2);
    void botRange() {
        if (x - BAT_RADIUS < 0) x = BAT_RADIUS;
        if (x + BAT_RADIUS > BOARD_WIDTH - 1) x = BOARD_WIDTH - BAT_RADIUS;
        if (y - BAT_RADIUS > SCREEN_HEIGHT / 2 - 1) y = SCREEN_HEIGHT / 2 - 1 - BAT_RADIUS;
        if (y - BAT_RADIUS < - 1) y = 0 + 1 + BAT_RADIUS;
    }
};
struct Disk{
    bool player_win = 0;
    bool bot_win = 0;
    double x,y;
    double dx = 0, dy = 0;
    double max_speed = MAX_DISK_SPEED;
    double decceleration = DECCELERATION;
    void wallHit(){
        if (y - DISK_RADIUS <= 0){
            y = DISK_RADIUS;
        }
        else if (y + DISK_RADIUS >= SCREEN_HEIGHT){
            y = SCREEN_HEIGHT - DISK_RADIUS;
        }
        dy = -dy;
    }
    void wallHitSide(){
        if (x - DISK_RADIUS <= 0){
            x = DISK_RADIUS;
        }
        else if (x + DISK_RADIUS >= BOARD_WIDTH){
            x = BOARD_WIDTH - DISK_RADIUS;
        }
        dx = -dx;
    }
    void collision(const Bat& bat){
        double hyp = hypot(bat.x - x, bat.y - y);
        double sin = (bat.y - y) / hyp;
        double cos = (bat.x - x) / hyp;
        double nspeed = dx*cos - dy*sin;
        double tspeed = dx*sin + dy*cos;
        dx = tspeed * sin - nspeed * cos + bat.dx;
        dy = tspeed * cos + nspeed * sin + bat.dy;
        while(max_speed * max_speed < dx*dx + dy*dy ){
            dx *= decceleration;
            dy *= decceleration;
        }
        double overlap = DISK_RADIUS + BAT_RADIUS - hyp;
        if (overlap > 0) {
            x -= overlap * cos;
            y -= overlap * sin;
        }
    }
    void bot_collision(const Bot& bot){
        double hyp = hypot(bot.x - x, bot.y - y);
        double sin = (bot.y - y) / hyp;
        double cos = (bot.x - x) / hyp;
        double nspeed = dx*cos - dy*sin;
        double tspeed = dx*sin + dy*cos;
        dx = tspeed * sin - nspeed * cos + bot.dx;
        dy = tspeed * cos + nspeed * sin + bot.dy;
        while(max_speed * max_speed < dx*dx + dy*dy ){
            dx *= decceleration;
            dy *= decceleration;
        }
        double overlap = DISK_RADIUS + BAT_RADIUS - hyp;
        if (overlap > 0) {
            x -= overlap * cos;
            y -= overlap * sin;
        }
    }
    void movement(const Bat& bat,const Bot& bot,Graphics& graphics,Mix_Chunk* hit_sound, const bool& speed_up){
        if (pow(bat.x - x, 2)+pow(bat.y - y, 2) <= 4 * BAT_RADIUS * DISK_RADIUS + 2){
            graphics.play(hit_sound);
            collision(bat);
        }
        if (pow(bot.x - x, 2)+pow(bot.y - y, 2) <= 4 * BAT_RADIUS * DISK_RADIUS + 2){
            graphics.play(hit_sound);
            bot_collision(bot);
        }
        if (x + DISK_RADIUS >= BOARD_WIDTH - 2 || x - DISK_RADIUS <= 2){
            graphics.play(hit_sound);
            wallHitSide();
        }
        if (y + DISK_RADIUS >= SCREEN_HEIGHT - 2 && x + DISK_RADIUS >= GOAL_X1 && x - DISK_RADIUS <= GOAL_X2 ){
            bot_win = 1;
            return;
        }
        if (y - DISK_RADIUS <= 2 && x + DISK_RADIUS >= GOAL_X1 && x - DISK_RADIUS <= GOAL_X2 ){
            player_win = 1;
            return;
        }
        if (y + DISK_RADIUS >= SCREEN_HEIGHT - 2 || y - DISK_RADIUS <= 2){
            graphics.play(hit_sound);
            wallHit();
        }
        x += dx;
        y += dy;
        if (!speed_up){
            dx *= decceleration;
            dy *= decceleration;
        }
        if (abs(dx) < MINIMUM_DISK_SPEED && abs(dy) < MINIMUM_DISK_SPEED){
            dx = 0;
            dy = 0;
        }
    }
};

void behavior(Bot& bot,const Disk& disk){
    double predictX = disk.x + disk.dx;
    double predictY = disk.y + disk.dy;
    double distanceX = predictX - bot.x;
    double distanceY = predictY - bot.y;
    bot.dx = bot.speed < distanceX ? bot.speed : distanceX;
    if (predictY > SCREEN_HEIGHT / 2){
        bot.dy = (bot.y > SCREEN_HEIGHT/5 ? -bot.speed : 0);
    }
    else if (predictY < bot.y + BAT_RADIUS ){
        bot.dy = -bot.speed;
    }
    else {
        bot.dy = (bot.speed < distanceY ? bot.speed : distanceY);
    }
    while (bot.speed*bot.speed < bot.dx*bot.dx + bot.dy*bot.dy){
        bot.dx *= 0.98;
        bot.dy *= 0.98;
    }
    bot.x += bot.dx;
    bot.y += bot.dy;
    bot.botRange();
}


#endif // LOGIC_H_INCLUDED
