#include "entity/ball_entity.h"

#include "entity/entity.h"
#include "graphics/image/image.h"
#include "graphics/object2d.h"
#include "core/input.h"

#include <SDL_rect.h>
#include <cstdlib>
#include <iostream>

namespace Breakout {

BallEntity::BallEntity(float speed, Vector2<float> position, Vector2<int> size)
    : Engine::Entity(position, size), m_movement_direction(Vector2<int>{-1, 1}), m_speed(speed),
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

void BallEntity::physics_process(float delta_time, const std::vector<Entity*>& colliders){
    Vector2<float> movement_offset = Vector2<float>(m_movement_direction) * m_speed * delta_time;

    Vector2<float> next_position = get_position() + movement_offset;
    if (next_position.x <= 0.0 || next_position.x + m_size.x >= m_screen_corners.w)
    {
        movement_offset.x = -movement_offset.x;
        m_movement_direction.x = -m_movement_direction.x;
    }
    if (next_position.y <= 0.0)
    {
        movement_offset.y = -movement_offset.y;
        m_movement_direction.y = -m_movement_direction.y;
    }

    if (next_position.y + m_size.y >= m_screen_corners.h){
        // Out of screen. Game over? Life --?
    }

    for (Entity* entity: colliders){
        const SDL_Rect& collider_bounds = entity->get_collision_bounds();

        if (entity->is_colliding_with(*this))
        {
            Vector2<int> entity_center = {collider_bounds.x + collider_bounds.w/2, collider_bounds.y + collider_bounds.h/2};
            Vector2<int> center = get_center_position();
            Vector2<int> direction_to_ball = entity_center.direction_to(center);

            if (std::abs(direction_to_ball.x) > std::abs(direction_to_ball.y)){
                movement_offset.x = -movement_offset.x;
                m_movement_direction.x = -m_movement_direction.x;
            }
            else{
                movement_offset.y = -movement_offset.y;
                m_movement_direction.y = -m_movement_direction.y;
            }

            break;
        }
    }

    move(movement_offset);
}


void BallEntity::set_position(const Vector2<float>& position){
    Engine::Object2D::set_position(position);

    m_ball_sprite.set_position(position);
}

};