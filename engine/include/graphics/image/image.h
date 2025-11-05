#pragma once

#include "graphics/object2d.h"

#include "SDL2/SDL_rect.h"
#include "SDL_blendmode.h"
#include "math/vector.h"
#include <SDL_render.h>
#include <cstdint>
#include <memory>
#include <vector>
#include <cstddef>

class SDL_Surface;
class SDL_Renderer;
class SDL_Texture;

namespace Engine {

using SDLTexturePtr = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;

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

class Image: public Object2D{
public:
    Image();
    Image(Vector2<int> position, Vector2<int> size);
    Image(const char* texture_path, Vector2<int> position, Vector2<int> size,
        bool use_color_key = false, Vector3<uint8_t> color_key = {});
    
    virtual ~Image();

    virtual void render(SDL_Renderer* renderer);

    void set_color(const Vector3<uint8_t>& color, const uint8_t& alpha);
    void set_blend_mode(SDL_BlendMode blend_mode);

    SDL_Texture* get_texture() const;
    void set_texture_path(const char* texture_path);

    void add_image_clip(SDL_Rect clip_rect, Vector2<int> local_position = {});
    void remove_image_clip(const size_t clip_id);
    ImageClip& get_imape_clip(const size_t clip_id);


protected:
    virtual void draw(SDL_Renderer* renderer, SDL_Rect* clip_rect = nullptr);
    
    void draw_all_image_clips(SDL_Renderer* renderer);
    void draw_image_clip(SDL_Renderer* renderer, ImageClip& image_clip);
    void draw_image_clip(SDL_Renderer*, uint8_t image_clip_id);

private:
    const bool is_texture_loaded() const;
    bool load_texture(SDL_Renderer* target_renderer);

    void clear();

protected:
    std::string m_texture_path;
    SDLTexturePtr m_image_texture = {nullptr, nullptr};
    std::vector<ImageClip> m_image_clips;

    Vector3<uint8_t> m_color{255};
    uint8_t m_alpha{255};

    bool m_use_color_key;
    Vector3<uint8_t> m_color_key;

    bool m_loaded;

};

}