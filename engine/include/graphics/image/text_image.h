#pragma once

#include "core/game.h"
#include "graphics/image/image.h"

#include <SDL_ttf.h>
#include <SDL_render.h>
#include <cstdint>

namespace Engine {

class TextImage: public Image
{
public:
    TextImage();
    TextImage(std::string text, TTF_Font* font_ptr,
        Vector2<int> position = {}, Vector2<int> size = {32}, 
        Vector3<uint8_t> color = {0}, uint8_t alpha = 255);

    void set_text(const std::string& text);
    const std::string& get_text() const;

protected:
    void draw(SDL_Renderer* renderer, SDL_Rect* clip_rect) override;


private:
    void load_text_texture(SDL_Renderer* target_renderer, TTF_Font* font_ptr);

private:
    std::string m_text;
    bool m_text_updated{false};

    Vector3<uint8_t> m_color;
    uint8_t m_alpha;

};

}