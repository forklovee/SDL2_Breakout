#include "ui/button/button.h"
#include "core/game.h"
#include "core/input.h"
#include "graphics/object2d.h"

#include <SDL_render.h>
#include <SDL_ttf.h>
#include <cstdint>
#include <iostream>

namespace Engine {

Button::Button(SDL_Renderer* renderer, std::string text, bool is_togglable,
  Vector2<int> position, Vector2<int> size, TTF_Font* font)
    : Object2D(position, size), m_text(text), m_is_pressed(false), m_is_toggleable(is_togglable),
      m_default_color(200), m_default_alpha(255),
      m_hover_color(235), m_hover_alpha(255),
      m_pressed_color(175), m_pressed_alpha(255),
      m_button_text_image(renderer, text, font, position, size),
      m_background_image(renderer, "", position, size)
{
  set_process_events(true);
  m_background_image.set_color({200, 0, 0}, 255);
}

Button::~Button()
{

}

void Button::render(SDL_Renderer* m_renderer)
{
  Vector3<uint8_t>& target_color = get_is_pressed() ? m_pressed_color : m_default_color;
  uint8_t& target_alpha = get_is_pressed() ? m_pressed_alpha : m_default_alpha;
  if (m_is_toggleable){
    if (!get_is_pressed() && m_mouse_state == Object2D::MouseState::MOUSE_OVER){
      target_color = m_hover_color;
      target_alpha = m_hover_alpha;
    }
  }
  else{
    switch(m_mouse_state)
    {
      case MouseState::MOUSE_OUT:
        target_color = m_default_color;
        target_alpha = m_default_alpha;
        break;
      case MouseState::MOUSE_OVER:
        target_color = m_hover_color;
        target_alpha = m_hover_alpha;
        break;
    }
  }

  m_background_image.set_color(target_color, target_alpha);

  m_background_image.render(m_renderer);
  m_button_text_image.render(m_renderer);
}

void Button::handle_event(const SDL_Event& event){
  Object2D::handle_event(event);

  if (!m_mouse_inside){
    return;
  }

  InputManager& input = InputManager::get_instance();
  if (m_is_toggleable && input.is_mouse_button_just_pressed()){
    set_is_pressed(!m_is_pressed);
  }
  else if(!m_is_toggleable){
    set_is_pressed(input.is_mouse_button_pressed());
  }
}


void Button::set_position(const Vector2<int>& position)
{
  // Object2D::set_position(position);
  m_background_image.set_position(position);
  m_button_text_image.set_position(position);
}

const bool& Button::get_is_pressed() const
{
  return m_is_pressed;
}


void Button::set_is_pressed(const bool& pressed)
{
  m_is_pressed = pressed;
}



}