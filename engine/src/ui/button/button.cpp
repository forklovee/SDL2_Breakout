#include "ui/button/button.h"
#include "core/game.h"
#include "graphics/object2d.h"

#include <SDL_render.h>
#include <SDL_ttf.h>
#include <iostream>

namespace Engine {

Button::Button(SDL_Renderer* renderer, std::string text, Vector2<int> position, Vector2<int> size, TTF_Font* font)
    : Object2D(position, size), m_text(text),
      m_default_color(200), m_default_alpha(255),
      m_hover_color(235), m_hover_alpha(255),
      m_pressed_color(175), m_pressed_alpha(255),
      m_button_text_image(renderer, text, font, position, size),
      m_background_image(renderer, "", position, size)
{
  m_background_image.set_color({200, 0, 0}, 255);
}

Button::~Button()
{

}

void Button::render(SDL_Renderer* m_renderer)
{
  switch(m_mouse_state)
  {
    case MouseState::MOUSE_OUT:
      m_background_image.set_color(m_default_color, m_default_alpha);
      break;
    case MouseState::MOUSE_OVER:
      m_background_image.set_color(m_hover_color, m_hover_alpha);
      break;
    case MouseState::MOUSE_BUTTON_PRESSED:
      m_background_image.set_color(m_pressed_color, m_pressed_alpha);
      break;
    case MouseState::MOUSE_BUTTON_RELEASED:
      m_background_image.set_color(m_hover_color, m_hover_alpha);
      break;
  }
  
  m_background_image.render(m_renderer);

  m_button_text_image.render(m_renderer);
}

void Button::handle_event(SDL_Event* event)
{
  Object2D::handle_event(event);
}


void Button::set_position(const Vector2<int>& position)
{
  // Object2D::set_position(position);
  m_background_image.set_position(position);
  m_button_text_image.set_position(position);
}


}