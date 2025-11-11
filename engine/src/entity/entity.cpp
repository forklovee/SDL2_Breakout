#include "entity/entity.h"
#include "graphics/object2d.h"
#include <SDL_rect.h>
#include <iostream>

namespace Engine{

Entity::Entity(Vector2<float> position, Vector2<int> size)
    :Object2D(position, size),
    m_collision_enabled(true)
{

}

void Entity::physics_process(float delta_time, const std::vector<std::unique_ptr<Entity>>& colliders){
    for (const auto& entity: colliders){
        if (entity.get() == this){ //omit self
            continue;
        }

        const SDL_Rect& collider_bounds = entity->get_collision_bounds();

        if (is_colliding_with(*entity))
        {
            entity->on_collision(this);
            this->on_collision(entity.get());
        }
    }
}

void Entity::on_collision(Entity* other_entity){
    std::cout << "Entity(" << this << ")" << " collided with " << other_entity << "\n";
}

void Entity::move(Vector2<float> offset){
    set_position(get_position() + offset);
}

const bool Entity::is_colliding_with(const Entity& other_entity){
    if (!m_collision_enabled){
        return false;
    }

    const SDL_Rect& this_collider = get_collision_bounds();
    const SDL_Rect& other_entity_collider = other_entity.get_collision_bounds();

    if (this_collider.x + this_collider.w >= other_entity_collider.x &&
        this_collider.x <= other_entity_collider.x + other_entity_collider.w &&
        this_collider.y + this_collider.h >= other_entity_collider.y &&
        this_collider.y <= other_entity_collider.y + other_entity_collider.h)
    {
        return true;
    }

    return false;
}


const SDL_Rect Entity::get_collision_bounds() const{
    return get_transform();
}

void Entity::destroy(){
    delete this;
}

}