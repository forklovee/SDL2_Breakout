#pragma once

#include "core/game.h"
#include "graphics/image/text_image.h"
#include "graphics/object2d.h"

#include "math/vector.h"
#include <SDL_ttf.h>
#include <string>

namespace Engine{

class Button: Object2D
{
public:
    Button() = default;
    Button(SDL_Renderer* renderer, std::string text, Vector2<int> position, Vector2<int> size = {64}, 
        TTF_Font* font = Engine::default_font);
    
    virtual ~Button() override;

    void render(SDL_Renderer* m_renderer) override;
    void handle_event(SDL_Event* event) override;

    void set_position(const Vector2<int>& position) override;

private:
    
    std::string m_text;

    TextImage m_button_text_image;
    Image m_background_image;
};

}