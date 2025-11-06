#pragma once

#include "graphics/object2d.h"
#include "graphics/image/image.h"

namespace Breakout{

class Paddle: public Engine::Object2D{
public:
    Paddle(Vector2<float> position = {}, Vector2<int> size = {128, 32});

    virtual void render(SDL_Renderer* renderer) override;
    virtual void process(float delta_time) override;
    virtual void handle_event(const SDL_Event& event) override;

    virtual void set_position(const Vector2<float>& position) override;

private:
    int m_center_pos_x;

    int m_input_direction;
    float m_velocity;

    Engine::Image m_paddle_image;


};

}