#include "graphics/image/text_image.h"

#include "core/game.h"
#include "math/vector.h"

#include <SDL_blendmode.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <iostream>

namespace Engine {

TextImage::TextImage(std::string text, TTF_Font* font_ptr, 
    Vector2<int> position, Vector2<int> size, Vector3<uint8_t> color, uint8_t alpha)
: Image(position, size), m_text(text), m_text_updated(false), m_color(color), m_alpha(alpha)
{
    
}

void TextImage::draw(SDL_Renderer* renderer, SDL_Rect* clip_rect)
{
    if (m_text_updated){
        load_text_texture(renderer, default_font);
        m_text_updated = false;
    }
    
    Image::draw(renderer, clip_rect);
}


void TextImage::load_text_texture(SDL_Renderer* target_renderer, TTF_Font* font_ptr)
{
    SDL_Surface* text_surface = TTF_RenderText_Blended(font_ptr, m_text.c_str(), {0, 0,0, 255});
    if(text_surface == NULL)
    {
        std::cerr << "Unable to render text surface! Error: " << TTF_GetError() << std::endl;
        return;
    }
    SDL_Texture* raw_texture_ptr = SDL_CreateTextureFromSurface(target_renderer, text_surface);
    m_image_texture = SDLTexturePtr(raw_texture_ptr, SDL_DestroyTexture);
    SDL_SetTextureBlendMode(m_image_texture.get(), SDL_BLENDMODE_BLEND);

    SDL_FreeSurface(text_surface);
}

void TextImage::set_text(const std::string& text)
{
    m_text = text;
    m_text_updated = true;
}

const std::string& TextImage::get_text() const
{
    return m_text;
}

}