#include "Header.h"
using namespace std;

#define WIDTH 1920
#define HEIGHT 1080
#define FPS 24
#define frameDelay (1000/FPS)


SDL_Renderer* renderer = NULL;

Img::Image gui;
BackPack backPack(1350, 210);

// Coordinates for mouse position
int x, y;


int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
       std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("r/gamedev", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    //Loads image
    Img::SetRenderer(renderer);

    // Example inteface
    Img::LoadImage("assets/gui.png", gui);

    // Add weapons to your inventory
    backPack.AddWeapon("Arma 1", "assets/pistol.png", Pistol);
    backPack.AddWeapon("Arma 2", "assets/riffle.png", Shotgun);
    backPack.AddWeapon("Arma 3", "assets/sniper.png", SniperRiffle);
    backPack.AddWeapon("Arma 4", "assets/riffle.png", Pistol);    
    backPack.AddWeapon("Arma 5", "assets/pistol.png", Pistol);
    backPack.AddWeapon("Arma 6", "assets/pistol.png", Shotgun);
    backPack.AddWeapon("Arma 7", "assets/sniper.png", SniperRiffle);
    backPack.AddWeapon("Arma 8", "assets/riffle2.png", Pistol);    
    backPack.AddWeapon("Arma 9", "assets/sniper.png", SniperRiffle);
    backPack.AddWeapon("Arma 10", "assets/sniper.png", SniperRiffle);
    backPack.AddWeapon("Arma 11", "assets/riffle2.png", Pistol);
    gui.rect.x = 0;
    gui.rect.y = 0;

    SDL_Event event;
    bool quit = false;

    Uint32 frameStart;
    int frameTime;

    while (!quit) {

        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {

            // Get Mouse state each tick
            SDL_GetMouseState(&x, &y);

            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) { // ESC
                quit = true;
            }
            else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LEFT) { // Left key
                backPack.WeaponLeft();
            }            
            else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RIGHT) { // Right key
                backPack.WeaponRight();
            } 
            else if (event.type == SDL_MOUSEBUTTONDOWN) // ANY Mouse button pressed
            {
                backPack.ClickHold(x, y);
            }
            else if (event.type == SDL_MOUSEBUTTONUP) {
                backPack.ClickRelease(x, y);
                backPack.ClickWeapon(x, y);
            }
        }

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }

        // clear the screen
        SDL_RenderClear(renderer);

        //Do render and game logic
        GameLoop(window);

        // flip the backbuffer
        // this means that everything that we prepared behind the screens is actually shown
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void GameLoop(SDL_Window* window) {

    gui.rect.w = WIDTH;
    gui.rect.h = HEIGHT;
    SDL_RenderCopy(renderer, gui.texture, NULL, &gui.rect);

    // Render backpack
    backPack.RenderItems(renderer, x, y);
}