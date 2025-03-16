#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

struct Mouse {
    int x, y;
    int dx = 0, dy = 0;
    int speed = INITIAL_SPEED;
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
        dy= -speed; dx=speed;
    }
    void turnNorthWest(){
        dy= -speed; dx=-speed;
    }
    void turnSouthEast(){
        dy= speed; dx=speed;
    }
    void turnSouthWest(){
        dy= speed; dx=-speed;
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

void render(const Mouse& mouse, const Graphics& graphics) {
    SDL_SetRenderDrawColor(graphics.renderer, 0, 255, 0, 255); // green
    renderCircle(graphics.renderer, mouse.x, mouse.y, CIRCLE_RADIUS); // Vẽ hình tròn với bán kính 5
}

bool gameOver(const Mouse& mouse) {
    return (mouse.x-CIRCLE_RADIUS) < 0 || mouse.x+CIRCLE_RADIUS >= SCREEN_WIDTH ||
           mouse.y-CIRCLE_RADIUS < 0 || mouse.y+CIRCLE_RADIUS >= SCREEN_HEIGHT;
}
void moveimage(Mouse &mouse,Graphics &graphics){
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        bool moved=false;
        if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
            mouse.turnNorthEast();
            moved = true;
        }

        else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_LEFT]) {
            mouse.turnNorthWest();
            moved = true;
        }

        else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
            mouse.turnSouthEast();
            moved = true;
        }

        else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_LEFT]) {
            mouse.turnSouthWest();
            moved = true;
        }

        else if (currentKeyStates[SDL_SCANCODE_UP]) {
            mouse.turnNorth();
            moved = true;
        }
        else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
            mouse.turnSouth();
            moved = true;
        }
        else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            mouse.turnWest();
            moved = true;
        }
        else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            mouse.turnEast();
            moved = true;
        }
        if (moved){
            mouse.move();
        }
        render(mouse, graphics);
}
#endif // LOGIC_H_INCLUDED
