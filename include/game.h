#ifndef GAME_H
#define GAME_H

#include "consts.h"
#include "commons.h"

class Game{
public:
    Game(const char* title, int window_height, int window_width);
    ~Game();

    void run();

private:
    void process_input();
    void update();
    void render();

    bool init(const char* title);
    void clear();

private:
    SDL_Window* m_window;
    SDL_Surface* m_screen_surface;
    bool m_is_running;
    int m_window_height;
    int m_window_width;
};

#endif