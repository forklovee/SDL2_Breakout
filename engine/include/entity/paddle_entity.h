#pragma once

#include "entity/entity.h"
#include "graphics/image/image.h"
#include <SDL_rect.h>

namespace Breakout{

class Paddle: public Engine::Entity{
public:
    Paddle(float speed, Vector2<float> position = {}, Vector2<int> size = {128, 32});

    virtual void render(Engine::Window& target_window) override;
    virtual void process(float delta_time) override;
    virtual void physics_process(float delta_time, const std::vector<Engine::Entity*>& colliders) override;

    virtual void handle_event(const SDL_Event& event) override;

    virtual void set_position(const Vector2<float>& position) override;

private:
    int m_center_pos_x;

    float m_speed;
    int m_input_direction;

    Engine::Image m_paddle_image;

    SDL_Rect m_collision_shape;

};

}