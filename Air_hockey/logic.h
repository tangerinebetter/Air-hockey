#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

void renderCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

struct Bat {
    double x, y;
    double dx = 0, dy = 0;
    bool moved=false;
    double speed = NORMAL_SPEED;
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
        dy= -diagonalSpeed; dx=diagonalSpeed;
    }
    void turnNorthWest(){
        dy= -diagonalSpeed; dx=-diagonalSpeed;
    }
    void turnSouthEast(){
        dy= diagonalSpeed; dx=diagonalSpeed;
    }
    void turnSouthWest(){
        dy= diagonalSpeed; dx=-diagonalSpeed;
    }
    void stayStill(){
        dx = 0 ;dy = 0;
    }
    void playRange() {
        if (x - BAT_RADIUS < 0) x = BAT_RADIUS;
        if (x + BAT_RADIUS > SCREEN_WIDTH - 1) x = SCREEN_WIDTH - BAT_RADIUS;
        if (y - BAT_RADIUS < SCREEN_HEIGHT / 2 - 1) y = SCREEN_HEIGHT / 2 - 1 + BAT_RADIUS;
        if (y + BAT_RADIUS > SCREEN_HEIGHT - 1) y = SCREEN_HEIGHT - 1 - BAT_RADIUS;
    }
    void renderBat(const Graphics& graphics) {
        SDL_SetRenderDrawColor(graphics.renderer, 0, 255, 0, 255);
        renderCircle(graphics.renderer, x, y, BAT_RADIUS);
    }
};

struct Disk{
    double x,y;
    double dx=0,dy=0;
    double decceleration=0.99;
    void renderDisk(const Graphics& graphics){
        SDL_SetRenderDrawColor(graphics.renderer, 255, 0, 0, 255);
        renderCircle(graphics.renderer, x, y, DISK_RADIUS);
    }
    void wallHit(){
        dy=-dy;
    }
    void wallHitSide(){
        dx=-dx;
    }
    void collision(const Bat& bat){
        double hyp=hypot(bat.x-x,bat.y-y);
        double sin=(bat.y-y)/hyp;
        double cos=(bat.x-x)/hyp;
        double nspeed = dx*cos - dy*sin;
        double tspeed = dx*sin + dy*cos;
        nspeed=-nspeed;
        dx = tspeed * sin + nspeed * cos + bat.dx;
        dy = tspeed * cos - nspeed * sin + bat.dy;
        while(MAX_DISK_SPEED*MAX_DISK_SPEED<dx*dx+dy*dy){
            dx*=0.98;
            dy*=0.98;
        }
    }
    void movement(const Bat&bat,const Graphics& graphics){
        if (pow(bat.x-x,2)+pow(bat.y-y,2)<=4*BAT_RADIUS*DISK_RADIUS+2){
            collision(bat);
        }
        if (x+DISK_RADIUS>=SCREEN_WIDTH-2||x-DISK_RADIUS<=2){
            wallHitSide();
        }
        if (y+DISK_RADIUS>=SCREEN_HEIGHT-2||y-DISK_RADIUS<=2){
            wallHit();
        }
        x+=dx;y+=dy;
        dx*=decceleration;dy*=decceleration;
        if (abs(dx)<0.2 && abs(dy)<0.2){
            dx = 0;
            dy = 0;
        }
        renderDisk(graphics);
    }
};

struct Bot{
    double x, y;
    double dx = 0, dy = 0;
    bool moved=false;
    double speed = NORMAL_SPEED;
    double diagonalSpeed = speed/sqrt(2);
};

void moveimage(Bat &bat,const Graphics &graphics){
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        bat.moved=false;
        /*if (currentKeyStates[SDL_SCANCODE_LSHIFT]){
            bat.speed = INITIAL_SPEED*2;
        }
        else {
            bat.speed = INITIAL_SPEED;
        } demo nut shift*/
        if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
            bat.turnNorthEast();
            bat.moved = true;
        }

        else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_LEFT]) {
            bat.turnNorthWest();
            bat.moved = true;
        }

        else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
            bat.turnSouthEast();
            bat.moved = true;
        }

        else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_LEFT]) {
            bat.turnSouthWest();
            bat.moved = true;
        }

        else if (currentKeyStates[SDL_SCANCODE_UP]) {
            bat.turnNorth();
            bat.moved = true;
        }
        else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
            bat.turnSouth();
            bat.moved = true;
        }
        else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            bat.turnWest();
            bat.moved = true;
        }
        else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            bat.turnEast();
            bat.moved = true;
        }
        if (bat.moved){
            bat.move();
        }
        else if (!bat.moved){
            bat.stayStill();
        }
        bat.playRange();
        bat.renderBat(graphics);
}
#endif // LOGIC_H_INCLUDED
