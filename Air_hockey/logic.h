#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

struct Bat {
    double x, y;
    double dx = 0, dy = 0;
    bool moved=false;
    double speed = INITIAL_SPEED;
    double diaspeed = speed/sqrt(2);
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
        dy= -diaspeed; dx=diaspeed;
    }
    void turnNorthWest(){
        dy= -diaspeed; dx=-diaspeed;
    }
    void turnSouthEast(){
        dy= diaspeed; dx=diaspeed;
    }
    void turnSouthWest(){
        dy= diaspeed; dx=-diaspeed;
    }
};

struct Disk{
    double x,y;
    double dx=0,dy=0;
    double decceleration=0.99;
    void movement(){
        x+=dx;y+=dy;
        dx*=decceleration;dy*=decceleration;

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
};

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

void render(const Bat& bat, const Graphics& graphics) {
    SDL_SetRenderDrawColor(graphics.renderer, 0, 255, 0, 255);
    renderCircle(graphics.renderer, bat.x, bat.y, CIRCLE_RADIUS);
}

void renderDisk(const Disk& disk,const Graphics& graphics){
    SDL_SetRenderDrawColor(graphics.renderer, 255, 0, 0, 255);
    renderCircle(graphics.renderer, disk.x, disk.y, CIRCLE_RADIUS);
}

bool gameOver(const Bat& bat) {
    return (bat.x-CIRCLE_RADIUS) < 0 || bat.x+CIRCLE_RADIUS >= SCREEN_WIDTH ||
           bat.y-CIRCLE_RADIUS < 0 || bat.y+CIRCLE_RADIUS >= SCREEN_HEIGHT;
}

void diskmovement(Disk& disk,const Bat& bat,Graphics& graphics){
    if (pow(bat.x-disk.x,2)+pow(bat.y-disk.y,2)<=4*CIRCLE_RADIUS*CIRCLE_RADIUS){
        disk.collision(bat);
    }
    if (disk.x+CIRCLE_RADIUS>=SCREEN_WIDTH-1||disk.x-CIRCLE_RADIUS<=0){
        disk.wallHitSide();
    }
    if (disk.y+CIRCLE_RADIUS>=SCREEN_HEIGHT-1||disk.y-CIRCLE_RADIUS<=0){
        disk.wallHit();
    }
    disk.movement();
    renderDisk(disk,graphics);
}

void moveimage(Bat &bat,Graphics &graphics){
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        bat.moved=false;
        if (currentKeyStates[SDL_SCANCODE_LSHIFT]){
            bat.speed = INITIAL_SPEED*2;
        }
        else {
            bat.speed = INITIAL_SPEED;
        }
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
        /*else if (!bat.moved){
            SDL_Delay(100);
            bat.dx=0;
            bat.dy=0;
        }*/
        render(bat, graphics);
}
#endif // LOGIC_H_INCLUDED
