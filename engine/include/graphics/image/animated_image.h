#pragma once

#include "image.h"

class AnimatedImage : public Image
{
public:
    AnimatedImage() = default;
    AnimatedImage(SDL_Renderer* target_renderer, const char* texture_path, Vector2<int> size, 
        uint8_t frames, bool use_color_key = false, Vector3<uint8_t> color_key = {});
    ~AnimatedImage() = default;

    void render(SDL_Renderer* renderer) override;

    void set_size(const Vector2<int>& size) override;

    void set_position(const Vector2<int>& position) override;

private:
    uint8_t frames = 0;
    uint8_t current_frame = 0;
};