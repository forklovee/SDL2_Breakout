#include "graphics/image/image.h"
#include "graphics/object2d.h"

#include "SDL_error.h"
#include "SDL_image.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include <iostream>

namespace Engine {

Image::Image(SDL_Renderer* target_renderer, const char* texture_path, Vector2<int> position, Vector2<int> size, bool use_color_key, Vector3<uint8_t> color_key)
    :Object2D(position, size), m_image_texture(nullptr)
{
    if (use_color_key){
        load_texture(texture_path, target_renderer, color_key);
    }
    else{
        load_texture(texture_path, target_renderer);
    }
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
    draw_all_image_clips(renderer);
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
    m_image_clips.push_back(ImageClip(clip_rect, m_position + local_position));
}

void Image::remove_image_clip(const size_t clip_id){
    m_image_clips.erase(m_image_clips.begin()+clip_id);
}

ImageClip& Image::get_imape_clip(const size_t clip_id){
    return m_image_clips[clip_id];
}



void Image::draw(SDL_Renderer* renderer, SDL_Rect* clip_rect)
{
    SDL_Rect transform = get_transform();   
    if(clip_rect != NULL){
        transform.w = clip_rect->w;
        transform.h = clip_rect->h;
    }

    if(m_image_texture == nullptr){
        SDL_RenderDrawRect(renderer, &transform);
        return;
    }

    SDL_RenderCopyEx(renderer, m_image_texture, clip_rect, &transform,
        get_rotation(), &get_pivot_point(), get_flipmode());
}

void Image::draw_all_image_clips(SDL_Renderer* renderer)
{
    for (ImageClip& image_clip : m_image_clips)
    {
        draw_image_clip(renderer, image_clip);
    }
}

void Image::draw_image_clip(SDL_Renderer* renderer, ImageClip& image_clip)
{
    SDL_RenderCopyEx(renderer, m_image_texture, &image_clip.clip_rect, &image_clip.destination_rect,
        get_rotation(), &get_pivot_point(), get_flipmode());
}

void Image::draw_image_clip(SDL_Renderer* renderer, uint8_t image_clip_id)
{
    draw_image_clip(renderer, m_image_clips[image_clip_id]);
}

bool Image::load_texture(const char* texture_path, SDL_Renderer* target_renderer)
{
    std::cout << "Image: Load texture from path: " << texture_path << "." << std::endl;

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
    std::cout << "Clear Image" << std::endl;

    SDL_DestroyTexture(m_image_texture);
    m_image_texture = nullptr;
}

}