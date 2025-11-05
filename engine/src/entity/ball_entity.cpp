#include "entity/ball_entity.h"

#include "graphics/image/image.h"
#include "graphics/object2d.h"
#include <iostream>

namespace Breakout {

BallEntity::BallEntity(Vector2<int> position, Vector2<int> size)
    : Engine::Object2D(position, size),
    m_ball_sprite("assets/images/Ball.png", position, size)
{
    m_ball_sprite.set_color({255, 0, 0}, 255);
}


void BallEntity::render(SDL_Renderer* renderer){
    m_ball_sprite.render(renderer);
}

void BallEntity::process(float delta_time){
    Vector2<int> target_position = get_position() + Vector2{0, 10} * delta_time;
    set_position(target_position);

}


void BallEntity::set_position(const Vector2<int>& position){
    Engine::Object2D::set_position(position);

    m_ball_sprite.set_position(position);
}

};