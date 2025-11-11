#pragma once

#include "graphics/object2d.h"
#include "math/vector.h"

#include <memory>
#include <vector>
#include <SDL_rect.h>

namespace Engine{
    
class Entity: public Object2D{

public:
    Entity(Vector2<float> position = {}, Vector2<int> size = {64});

    virtual void physics_process(float delta_time, const std::vector<std::unique_ptr<Entity>>& colliders);

    void move(Vector2<float> offset);

    const bool is_colliding_with(const Entity& other_entity);
    const SDL_Rect get_collision_bounds() const;

    virtual void destroy();

protected:
    virtual void on_collision(Entity* other_entity);

protected:
    bool m_collision_enabled;

};

}