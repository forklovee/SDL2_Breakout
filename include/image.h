#pragma once

#include "SDL2/SDL_rect.h"
#include "vector.h"

class SDL_Surface;
class SDL_Renderer;
class SDL_Texture;

class Image{
public:
    Image(const char* texture_path, SDL_Renderer* target_renderer);
    Image(const char* texture_path, SDL_Renderer* target_renderer, Vector3i color_key);
    ~Image();

    void draw(SDL_Renderer* target_renderer);

    void set_positon(const Vector2i& position);
    void set_size(const Vector2i& size);

    SDL_Texture* get_texture() const;

private:
    bool load_texture(const char* texture_path, SDL_Renderer* target_renderer);
    bool load_texture(const char* texture_path, SDL_Renderer* target_renderer, Vector3i& color_key);
    void clear();

private:
    SDL_Texture* m_image_texture;
    SDL_Rect m_position_and_size;

};
