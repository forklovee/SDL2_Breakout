#pragma once

#include <string>

#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_video.h>

#include "math/vector.h"

namespace Engine{

class Window{
public:
    Window() = default;
    Window(std::string window_name, Vector2<int> size, Vector2<int> position = {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED});
    ~Window();

    SDL_Renderer* get_renderer() const;

    void clear_renderer() const;
    void update_renderer() const;

    const SDL_Rect& get_window_transform() const;
    Vector2<int> get_window_position() const;
    Vector2<int> get_window_size() const;

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    std::string m_name;
    SDL_Rect m_window_transform;

};

}