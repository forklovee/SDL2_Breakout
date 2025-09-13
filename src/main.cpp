#include <cstdio>
#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "game.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]){
    #ifdef _WIN32
        AllocConsole();
        FILE* fp;
        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONOUT$", "w", stderr);
    #endif
    
    Game game("Breakout", 600, 400);
    game.run();

    return 0;
}