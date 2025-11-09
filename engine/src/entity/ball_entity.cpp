#include "entity/ball_entity.h"

#include "graphics/image/image.h"
#include "graphics/object2d.h"
#include "core/input.h"

#include <iostream>

namespace Breakout {

BallEntity::BallEntity(Vector2<float> position, Vector2<int> size)
    : Engine::Object2D(position, size), m_velocity({1.0}),
    m_ball_sprite("assets/images/Ball.png", position, size)
{
    m_ball_sprite.set_color({255, 0, 0}, 255);
}


void BallEntity::render(Engine::Window& target_window){
    m_ball_sprite.render(target_window);
}

void BallEntity::process(float delta_time){
    Vector2<float> target_position = get_position();
    target_position += m_velocity * 100.f * delta_time;

    set_position(target_position);
}

void BallEntity::set_position(const Vector2<float>& position){
    Engine::Object2D::set_position(position);

    m_ball_sprite.set_position(position);
}

};