#pragma once

#include "math/vector.h"
#include <SDL_render.h>
#include <SDL_events.h>

namespace Engine{

class Object2D
{
public:
    enum class MouseState{
        MOUSE_OUT,
        MOUSE_OVER,
        MOUSE_BUTTON_PRESSED,
        MOUSE_BUTTON_RELEASED
    };


    Object2D() = default;
    Object2D(Vector2<int> position, Vector2<int> size);
    virtual ~Object2D();

    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void handle_event(SDL_Event* event);

    SDL_Rect get_transform() const;

    const Vector2<int>& get_position() const;
    virtual void set_position(const Vector2<int>& position);

    const Vector2<int>& get_size() const;
    virtual void set_size(const Vector2<int>& size);

    const SDL_Point& get_pivot_point() const;
    virtual void set_pivot_point(const SDL_Point& pivot_point);

    const double& get_rotation() const;
    virtual void set_rotation(const double& rotation);

    const SDL_RendererFlip& get_flipmode() const;
    virtual void set_flipmode(const SDL_RendererFlip& flipmode);

protected:
    Vector2<int> m_position{};    
    Vector2<int> m_size{};

    SDL_Point m_pivot_point{};
    double m_rotation{0.0};

    SDL_RendererFlip m_flipmode{SDL_FLIP_NONE};

    MouseState m_mouse_state{MouseState::MOUSE_OUT};
};

};