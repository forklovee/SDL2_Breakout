#pragma once

#include "entity/entity.h"

#include "graphics/image/image.h"
#include "math/vector.h"
#include <SDL_rect.h>

namespace Breakout{

class BallEntity: public Engine::Entity{
public:
    BallEntity(float speed = 150.f, Vector2<float> position = {}, Vector2<int> size = {16});

    virtual void render(Engine::Window& target_window) override;
    virtual void process(float delta_time) override;

    virtual void physics_process(float delta_time, const std::vector<Entity*>& colliders) override;

    virtual void set_position(const Vector2<float>& position) override;

private:
    Vector2<int> m_movement_direction;
    float m_speed;

    SDL_Rect m_screen_corners;
    Engine::Image m_ball_sprite;
};

}