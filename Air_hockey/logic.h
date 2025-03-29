#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

struct Mallet {
    double x, y;
    double dx = 0, dy = 0;
    bool moved;
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
        x+=dx; y+=dy;
        dx*=decceleration;dy*=decceleration;
    }
    void wallHit(){
        dy=-dy;
    }
    void wallHitSide(){
        dx=-dx;
    }
    void collision(double a,double b){
        dx=a;
        dy=b;
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

void render(const Mallet& mouse, const Graphics& graphics) {
    SDL_SetRenderDrawColor(graphics.renderer, 0, 255, 0, 255); // green
    renderCircle(graphics.renderer, mouse.x, mouse.y, CIRCLE_RADIUS); // Vẽ hình tròn với bán kính 5
}

void renderDisk(const Disk& disk,const Graphics& graphics){
    SDL_SetRenderDrawColor(graphics.renderer, 255, 0, 0, 255); // green
    renderCircle(graphics.renderer, disk.x, disk.y, CIRCLE_RADIUS);
}

bool gameOver(const Mallet& mouse) {
    return (mouse.x-CIRCLE_RADIUS) < 0 || mouse.x+CIRCLE_RADIUS >= SCREEN_WIDTH ||
           mouse.y-CIRCLE_RADIUS < 0 || mouse.y+CIRCLE_RADIUS >= SCREEN_HEIGHT;
}

void diskmovement(Disk& disk,const Mallet& mallet,Graphics& graphics){
    if (pow(mallet.x-disk.x,2)+pow(mallet.y-disk.y,2)<=4*CIRCLE_RADIUS*CIRCLE_RADIUS){
        if (mallet.moved)disk.collision(mallet.dx,mallet.dy);
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

void moveimage(Mallet &mouse,Graphics &graphics){
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        mouse.moved=false;
        if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
            mouse.turnNorthEast();
            mouse.moved = true;
        }

        else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_LEFT]) {
            mouse.turnNorthWest();
            mouse.moved = true;
        }

        else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
            mouse.turnSouthEast();
            mouse.moved = true;
        }

        else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_LEFT]) {
            mouse.turnSouthWest();
            mouse.moved = true;
        }

        else if (currentKeyStates[SDL_SCANCODE_UP]) {
            mouse.turnNorth();
            mouse.moved = true;
        }
        else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
            mouse.turnSouth();
            mouse.moved = true;
        }
        else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            mouse.turnWest();
            mouse.moved = true;
        }
        else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            mouse.turnEast();
            mouse.moved = true;
        }
        if (mouse.moved){
            mouse.move();
        }
        render(mouse, graphics);
}
#endif // LOGIC_H_INCLUDED
