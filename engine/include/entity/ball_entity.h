#pragma once

#include "graphics/image/image.h"
#include "graphics/object2d.h"
#include "math/vector.h"
#include <cstdint>

namespace Breakout{

class BallEntity: public Engine::Object2D{
public:
    BallEntity(Vector2<int> position, Vector2<int> size);

    virtual void render(SDL_Renderer* renderer) override;
    virtual void process(float delta_time) override;

    virtual void set_position(const Vector2<int>& position) override;

private:
    Vector2<int> m_velocity;

    Engine::Image m_ball_sprite;
};

}