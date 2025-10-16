#include "graphics/image/image.h"

#include "SDL_error.h"
#include "SDL_image.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "math/vector.h"
#include <vector>
#include <iostream>

Image::Image(const char* texture_path, SDL_Renderer* target_renderer)
    :m_image_texture(nullptr)
{
    load_texture(texture_path, target_renderer);
}

Image::Image(const char* texture_path, SDL_Renderer* target_renderer, Vector3<uint8_t> color_key)
    :m_image_texture(nullptr)
{
    load_texture(texture_path, target_renderer, color_key);
}

Image::~Image()
{
    clear();
}

void Image::render(SDL_Renderer* renderer)
{
    if (m_image_clips.empty()){
        draw(renderer);
        return;
    }
    draw_image_clips(renderer);
}

Vector2<int> Image::get_position() const
{
    return m_position;
}

void Image::set_positon(const Vector2<int>& position)
{
    m_position.x = position.x;
    m_position.y = position.y;
}

Vector2<int> Image::get_size() const
{
    return m_size;
};


void Image::set_size(const Vector2<int>& size)
{
    m_size.x = size.x;
    m_size.x = size.y;
}

void Image::set_color(const Vector3<uint8_t>& color, const uint8_t& alpha)
{
    SDL_SetTextureColorMod(m_image_texture, color.x, color.y, color.z);
    SDL_SetTextureAlphaMod(m_image_texture, alpha);
}

void Image::set_blend_mode(SDL_BlendMode blend_mode)
{
    SDL_SetTextureBlendMode(m_image_texture, blend_mode);
}



SDL_Texture* Image::get_texture() const{
    return m_image_texture;
}

void Image::add_image_clip(SDL_Rect clip_rect, Vector2<int> local_position){
    m_image_clips.push_back(new ImageClip(clip_rect, m_position + local_position));
}

void Image::remove_image_clip(const size_t clip_id){
    ImageClip* image_clip = &get_imape_clip(clip_id);
    m_image_clips.erase(std::next(m_image_clips.begin()+clip_id));
    delete image_clip;
}

ImageClip& Image::get_imape_clip(const size_t clip_id){
    return *m_image_clips[clip_id];
}



void Image::draw(SDL_Renderer* renderer, SDL_Rect* transform, SDL_Rect* clip_rect)
{
    if(!transform){
        SDL_Rect new_transform = SDL_Rect{m_position.x, m_position.y, m_size.x, m_size.y};
        transform = &new_transform;
    }
    
    if(clip_rect != NULL){
        transform->w = clip_rect->w;
        transform->h = clip_rect->h;
    }

    SDL_RenderCopy(renderer, m_image_texture, clip_rect, transform);
}

void Image::draw_image_clips(SDL_Renderer* renderer)
{
    for (ImageClip* image_clip_ptr : m_image_clips){
        
        draw(renderer, &image_clip_ptr->destination_rect, &image_clip_ptr->clip_rect);
    }
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

bool Image::load_texture(const char* texture_path, SDL_Renderer* target_renderer, Vector3<uint8_t>& color_key)
{
    std::cout << "Image: Load texture from path: " << texture_path << "." << std::endl;

    if (m_image_texture){
        clear();
    }

    SDL_Surface* image_surface = IMG_Load(texture_path);
    if (!image_surface){
        std::cerr << "Error! Couldn't create an image surface from " << texture_path << " image!" << IMG_GetError() << std::endl;
        return false;
    }

    SDL_SetColorKey(image_surface, SDL_TRUE, 
        SDL_MapRGB(image_surface->format, color_key.x, color_key.y, color_key.z));
    m_image_texture = SDL_CreateTextureFromSurface(target_renderer, image_surface);
    if (!m_image_texture){
        std::cerr << "Error! Couldn't create a texture from "<< texture_path << " image!" << SDL_GetError() << std::endl;
        return false;
    }
    SDL_FreeSurface(image_surface);
    return m_image_texture != nullptr;
}

void Image::clear()
{
    SDL_DestroyTexture(m_image_texture);
    m_image_texture = nullptr;
}