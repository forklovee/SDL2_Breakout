#pragma once

#include "core/window.h"
#include "image.h"

namespace Engine {

class AnimatedImage : public Image
{
public:
    AnimatedImage() = default;
    AnimatedImage(const char* texture_path, Vector2<float> position, Vector2<int> size,
        uint8_t frames, bool use_color_key = false, Vector3<uint8_t> color_key = {});
    ~AnimatedImage() = default;

    void render(Window& target_window) override;

    void set_position(const Vector2<float>& position) override;
    void set_size(const Vector2<int>& size) override;

private:
    uint8_t m_frames = 0;
    uint8_t m_current_frame = 0;
};

}