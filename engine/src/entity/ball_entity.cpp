#include "entity/ball_entity.h"

#include "entity/entity.h"
#include "graphics/image/image.h"
#include "graphics/object2d.h"
#include "core/input.h"

#include <SDL_rect.h>
#include <cstdlib>
#include <iostream>
#include <memory>

namespace Breakout {

BallEntity::BallEntity(float speed, Vector2<float> position, Vector2<int> size)
    : Engine::Entity(position, size), m_movement_direction(Vector2<int>{-1, -1}), m_speed(speed),
    m_ball_sprite("assets/images/Ball.png", position, size)
{
    m_ball_sprite.set_color({255, 0, 0}, 255);
}


void BallEntity::render(Engine::Window& target_window){
    m_screen_corners = target_window.get_window_transform();
    m_ball_sprite.render(target_window);
}

void BallEntity::process(float delta_time){
}

void BallEntity::physics_process(float delta_time, const std::vector<std::unique_ptr<Engine::Entity>>& colliders){

    if (m_position.x <= 0.0 || m_position.x + m_size.x >= m_screen_corners.w)
    {
        m_movement_direction.x = -m_movement_direction.x;
    }
    if (m_position.y <= 0.0)
    {
        m_movement_direction.y = -m_movement_direction.y;
    }

    if (m_position.y + m_size.y >= m_screen_corners.h){
        // Out of screen. Game over? Life --?
    }

    Engine::Entity::physics_process(delta_time, colliders);

    Vector2<float> movement_offset = Vector2<float>(m_movement_direction) * m_speed * delta_time;
    move(movement_offset);
}

void BallEntity::on_collision(Engine::Entity* entity){
    Engine::Entity::on_collision(entity);
    
    const SDL_Rect& collider_bounds = entity->get_collision_bounds();
    Vector2<int> entity_center = {collider_bounds.x + collider_bounds.w/2, collider_bounds.y + collider_bounds.h/2};
    Vector2<int> center = get_center_position();
    Vector2<int> direction_to_ball = entity_center.direction_to(center);

    if (std::abs(direction_to_ball.x) > std::abs(direction_to_ball.y)){
        m_movement_direction.x = -m_movement_direction.x;
    }
    else{
        m_movement_direction.y = -m_movement_direction.y;
    }

    std::cout << "col[ pos:" << entity->get_position() << " size:" << entity->get_size() << "]\n";
    std::cout << "ball[ pos:" << get_position() << " size:" << get_size() << "]\n";
}

void BallEntity::set_position(const Vector2<float>& position){
    Engine::Object2D::set_position(position);

    m_ball_sprite.set_position(position);
}

};