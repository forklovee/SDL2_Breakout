#define SDL_MAIN_HANDLED

#include <cstdio>
#include <stdio.h>

#include <SDL2/SDL.h>
#include "core/game.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]){
    #ifdef _WIN32
        AllocConsole();
        FILE* fp;
        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONOUT$", "w", stderr);
        
        freopen_s(&fp, "CONIN$", "r", stdin);
    #endif

    Engine::Game* game = new Engine::Game("Breakout", 600, 400);
    game->run();
    delete game;

    return 0;
}