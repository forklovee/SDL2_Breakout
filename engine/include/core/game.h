#pragma once

#include "core/timing.h"
#include "graphics/object2d.h"
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

#pragma region FPS

    void set_fps_cap_enabled(bool state);
    const bool& get_fps_cap_enabled() const;
    
    void set_fps_cap(uint16_t fps_cap);
    const uint16_t& get_fps_cap() const;

#pragma endregion FPS

private:
    void start();

    void process_input();
    void update();
    void render();

    bool init(const char* title);
    void clear();

    const int get_screen_ticks_per_frame();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Surface* m_screen_surface;
    bool m_is_running;
    int m_window_height;
    int m_window_width;

    Timer m_timer;
    uint32_t m_counted_frames;

    Timer m_step_timer;

    bool m_fps_cap_enabled;
    Timer m_cap_timer;
    uint16_t m_fps_cap;

    std::vector<TTF_Font*> fonts;
    std::vector<Object2D*> objects;

};

}
