#include "graphics/image/animated_image.h"
#include <iostream>

AnimatedImage::AnimatedImage(SDL_Renderer* target_renderer, const char* texture_path, Vector2<int> size,
    uint8_t frames, bool use_color_key, Vector3<uint8_t> color_key)
    : Image(target_renderer, texture_path, size, use_color_key, color_key)
{
    std::cout << "AnimatedImage!" << get_size() << std::endl;

    this->frames = frames;
    for(uint8_t clip_id = 0; clip_id < this->frames; clip_id++){
        add_image_clip(SDL_Rect{
            get_size().x * clip_id,0,
            get_size().x, get_size().y
        });
    }
}

void AnimatedImage::render(SDL_Renderer* renderer)
{
    Image::render(renderer);

    current_frame++;
    uint8_t animation_frame = current_frame / frames;
    if (animation_frame >= frames)
    {
        animation_frame = 0;
        current_frame = 0;
    }

    ImageClip& image_clip = m_image_clips[animation_frame];
    // std::cout << "AnimatedImage frame: " << image_clip.clip_rect.x << "," << image_clip.clip_rect.y <<
        // " " << image_clip.destination_rect.x << "," << image_clip.destination_rect.y << std::endl;

    draw_image_clip(renderer, m_image_clips[animation_frame]);
}

void AnimatedImage::set_size(const Vector2<int> &size)
{
    Image::set_size(size);
    uint8_t clip_id = 0;
    for(ImageClip& image_clip_ptr : m_image_clips)
    {
        image_clip_ptr.clip_rect.x = clip_id * size.x;
        image_clip_ptr.clip_rect.y = 0;
        image_clip_ptr.clip_rect.w = size.x;
        image_clip_ptr.clip_rect.h = size.y;

        image_clip_ptr.destination_rect.w = size.x;
        image_clip_ptr.destination_rect.h = size.y;

        clip_id++;
    }
}

void AnimatedImage::set_position(const Vector2<int>& position)
{
    Image::set_position(position);
    for(ImageClip& image_clip_ptr : m_image_clips)
    {
        image_clip_ptr.destination_rect.x = position.x;
        image_clip_ptr.destination_rect.y = position.y;
    }
}
