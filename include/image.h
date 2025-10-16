#pragma once

#include "SDL2/SDL_rect.h"
#include "vector.h"
#include <vector>
#include <cstddef>

class SDL_Surface;
class SDL_Renderer;
class SDL_Texture;

struct ImageClip{
    SDL_Rect destination_rect;
    SDL_Rect clip_rect;

    ImageClip(SDL_Rect& clip_rect, Vector2<int> render_position){
        this->clip_rect = clip_rect;
        this->destination_rect = {
            render_position.x,
            render_position.y,
            clip_rect.w,
            clip_rect.h
        };
    }
};

class Image{
public:
    Image(const char* texture_path, SDL_Renderer* target_renderer);
    Image(const char* texture_path, SDL_Renderer* target_renderer, Vector3<uint8_t> color_key);
    ~Image();

    void render(SDL_Renderer* renderer);

    Vector2<int> get_position() const;
    void set_positon(const Vector2<int>& position);

    Vector2<int> get_size() const;
    void set_size(const Vector2<int>& size);

    void set_color(const Vector3<uint8_t>& color);

    SDL_Texture* get_texture() const;

    void add_image_clip(SDL_Rect clip_rect, Vector2<int> render_position);
    void remove_image_clip(const size_t clip_id);
    ImageClip& get_imape_clip(const size_t clip_id);


private:
    void draw(SDL_Renderer* renderer, SDL_Rect* transform = nullptr, SDL_Rect* clip_rect = nullptr);
    void draw_image_clips(SDL_Renderer* renderer);

    bool load_texture(const char* texture_path, SDL_Renderer* target_renderer);
    bool load_texture(const char* texture_path, SDL_Renderer* target_renderer, Vector3<uint8_t>& color_key);
    void clear();

private:
    SDL_Texture* m_image_texture;
    SDL_Rect m_position_and_size;

    std::vector<ImageClip*> m_image_clips;
};
