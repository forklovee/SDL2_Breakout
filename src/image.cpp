#include "image.h"

#include "SDL_error.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "vector.h"
#include <iostream>

Image::Image(const char* texture_path, SDL_Renderer* target_renderer)
    :m_image_texture(nullptr)
{
    if (load_texture(texture_path, target_renderer))
    {
        draw(target_renderer);
    }
}

Image::Image(const char* texture_path, SDL_Renderer* target_renderer, Vector3i color_key)
    :m_image_texture(nullptr)
{
    if (load_texture(texture_path, target_renderer, color_key))
    {
        draw(target_renderer);
    }
}

Image::~Image()
{
    clear();
    std::cout << "Image destroy" << std::endl;
}

void Image::draw(SDL_Renderer* target_renderer)
{
    SDL_RenderCopy(target_renderer, m_image_texture, NULL, NULL);
}

void Image::set_positon(const Vector2i& position)
{
    m_position_and_size.x = position.x;
    m_position_and_size.y = position.y;
}

void Image::set_size(const Vector2i& size)
{
    m_position_and_size.w = size.x;
    m_position_and_size.h = size.y;
}

SDL_Texture* Image::get_texture() const{
    return m_image_texture;
}

bool Image::load_texture(const char* texture_path, SDL_Renderer* target_renderer)
{
    if (m_image_texture){
        clear();
    }

    m_image_texture = IMG_LoadTexture(target_renderer, texture_path);
    if (!m_image_texture){
        std::cerr << "Error! Couldn't create a texture from "<< texture_path << " image!" << SDL_GetError() << std::endl;
        return false;
    }
    
    return m_image_texture != NULL;
}

bool Image::load_texture(const char* texture_path, SDL_Renderer* target_renderer, Vector3i& color_key)
{
    if (m_image_texture){
        clear();
    }

    SDL_Surface* image_surface = IMG_Load(texture_path);
    if (!image_surface){
        std::cerr << "Error! Couldn't create an image surface from " << texture_path << " image!" << IMG_GetError() << std::endl;
        return false;
    }

    SDL_SetColorKey(image_surface, SDL_TRUE, SDL_MapRGB(image_surface->format, color_key.x, color_key.y, color_key.z));
    m_image_texture = SDL_CreateTextureFromSurface(target_renderer, image_surface);
    if (!m_image_texture){
        std::cerr << "Error! Couldn't create a texture from "<< texture_path << " image!" << SDL_GetError() << std::endl;
        return false;
    }
    SDL_FreeSurface(image_surface);
    return m_image_texture != NULL;
}

void Image::clear()
{
    SDL_DestroyTexture(m_image_texture);
    m_image_texture = NULL;
}