#include "graphics/image/animated_image.h"
#include <iostream>

namespace Engine {

AnimatedImage::AnimatedImage(const char* texture_path, Vector2<float> position, Vector2<int> size,
    uint8_t frames, bool use_color_key, Vector3<uint8_t> color_key)
    : Image(texture_path, position, size, use_color_key, color_key), m_frames(frames)
{
    std::cout << "AnimatedImage!" << get_size() << std::endl;

    for(uint8_t clip_id = 0; clip_id < m_frames; clip_id++){
        add_image_clip(SDL_Rect{
            get_size().x * clip_id,0,
            get_size().x, get_size().y
        });
    }
}

void AnimatedImage::render(SDL_Renderer* renderer)
{
    Image::render(renderer);

    m_current_frame++;
    uint8_t animation_frame = m_current_frame / m_frames;
    if (animation_frame >= m_frames)
    {
        animation_frame = 0;
        m_current_frame = 0;
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

void AnimatedImage::set_position(const Vector2<float>& position)
{
    Image::set_position(position);
    for(ImageClip& image_clip_ptr : m_image_clips)
    {
        image_clip_ptr.destination_rect.x = static_cast<int>(position.x);
        image_clip_ptr.destination_rect.y = static_cast<int>(position.y);
    }
}

}