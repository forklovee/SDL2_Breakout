#pragma once

#include "core/window.h"
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
    Object2D(Vector2<float> position = {}, Vector2<int> size = {64});
    virtual ~Object2D();

    virtual void render(Window& target_window);
    virtual void process(float delta_time);
    virtual void handle_event(const SDL_Event& event);

    SDL_Rect get_transform() const;

    const Vector2<float>& get_position() const;
    virtual void set_position(const Vector2<float>& position);

    const Vector2<int>& get_size() const;
    virtual void set_size(const Vector2<int>& size);

    Vector2<int> get_center_position() const;

    const bool& is_visible() const;
    virtual void set_visible(const bool& is_visible);

    const SDL_Point& get_pivot_point() const;
    virtual void set_pivot_point(const SDL_Point& pivot_point);

    const double& get_rotation() const;
    virtual void set_rotation(const double& rotation);

    const SDL_RendererFlip& get_flipmode() const;
    virtual void set_flipmode(const SDL_RendererFlip& flipmode);

    const bool& get_process_events() const;
    virtual void set_process_events(const bool& process_events);

protected:
    Vector2<float> m_position{};
    Vector2<int> m_size{};
    bool m_visible;

    SDL_Point m_pivot_point{};
    double m_rotation{0.0};

    SDL_RendererFlip m_flipmode{SDL_FLIP_NONE};

    bool m_process_events{false};
    bool m_mouse_inside{false};
    MouseState m_mouse_state{MouseState::MOUSE_OUT};
};

};