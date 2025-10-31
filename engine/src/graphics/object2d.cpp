#include "graphics/object2d.h"
#include "core/input.h"
#include <SDL_events.h>
#include <iostream>

namespace Engine{

Object2D::Object2D(Vector2<int> position, Vector2<int> size) :
    m_position(position), m_size(size)
{

}

Object2D::~Object2D()
{

}

void Object2D::render(SDL_Renderer* renderer)
{

}


void Object2D::handle_event(const SDL_Event& event)
{
    bool mouse_inside = false;

    InputManager& input = InputManager::get_instance();

    Vector2<int>& mouse_position = input.get_mouse_position();
    if (mouse_position.x > m_position.x && mouse_position.x < m_position.x + m_size.x &&
        mouse_position.y > m_position.y && mouse_position.y < m_position.y + m_size.y)
    {
        mouse_inside = true;
    }

    m_mouse_state = mouse_inside ? MouseState::MOUSE_OVER : MouseState::MOUSE_OUT;

    if (!mouse_inside)
    {
        return;
    }

    if (input.is_mouse_button_pressed(false))
    {
        m_mouse_state = MouseState::MOUSE_BUTTON_PRESSED;
    }
    else
    {
        m_mouse_state = MouseState::MOUSE_BUTTON_RELEASED;
    }
}

SDL_Rect Object2D::get_transform() const
{
    return {
        m_position.x,
        m_position.y,
        m_size.x,
        m_size.y
    };
}

const Vector2<int>& Object2D::get_position() const
{
    return m_position;
}

void Object2D::set_position(const Vector2<int>& position)
{
    m_position = position;
}

const Vector2<int>& Object2D::get_size() const
{
    return m_size;
}

void Object2D::set_size(const Vector2<int>& size)
{
    m_size = {
        abs(size.x),
        abs(size.x),
    };
}

const SDL_Point& Object2D::get_pivot_point() const
{
    return m_pivot_point;
}
void Object2D::set_pivot_point(const SDL_Point& pivot_point)
{
    m_pivot_point = pivot_point;
}

const double& Object2D::get_rotation() const
{
    return m_rotation;
}
void Object2D::set_rotation(const double& rotation)
{
    m_rotation = rotation;
}

const SDL_RendererFlip& Object2D::get_flipmode() const
{
    return m_flipmode;
}
void Object2D::set_flipmode(const SDL_RendererFlip& flipmode)
{
    m_flipmode = flipmode;
}

};