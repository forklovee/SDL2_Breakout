#pragma once

#include "math/vector.h"

#include "SDL2/SDL_surface.h"
#include "SDL_render.h"
#include <SDL_ttf.h>
#include <vector>

namespace Engine{

class Image;
class Button;

static const char* ASSET_PATH = "../game/assets/";
extern TTF_Font* default_font;

// extern const TTF_Font* default_font;

class Game{
public:
    Game(const char* title, int window_height, int window_width);
    ~Game();

    void run();
    Vector2<int> get_screen_surface_size() const; 

private:
    void start();

    void process_input();
    void update();
    void render();

    bool init(const char* title);
    void clear();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Surface* m_screen_surface;
    bool m_is_running;
    int m_window_height;
    int m_window_width;

    std::vector<TTF_Font*> fonts;
    std::vector<Image*> images;
    std::vector<Button*> buttons;

};

}
