#include "ui/button/button.h"
#include "core/game.h"

#include <SDL_render.h>
#include <SDL_ttf.h>

namespace Engine {

Button::Button(SDL_Renderer* renderer, std::string text, Vector2<int> position, Vector2<int> size, TTF_Font* font)
    : Object2D(position, size), m_text(text),
      m_button_text_image(renderer, text, font, size),
      m_background_image(renderer, "", position, size)
{
}

Button::~Button()
{

}

void Button::render(SDL_Renderer* m_renderer)
{
  m_background_image.render(m_renderer);
  m_button_text_image.render(m_renderer);
}

void Button::handle_event(SDL_Event* event)
{

}


void Button::set_position(const Vector2<int>& position)
{
  // Object2D::set_position(position);
  m_background_image.set_position(position);
  m_button_text_image.set_position(position);
}


}