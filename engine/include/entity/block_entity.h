#pragma once

#include "entity/entity.h"
#include "graphics/image/image.h"
#include <cstdint>

namespace Breakout{

class BlockEntity: public Engine::Entity{
public:
    BlockEntity(Vector2<float> position = {}, Vector2<int> size = {64, 32});

    void set_color(Vector3<uint8_t> color, uint8_t alpha);

protected:
    virtual void on_collision(Entity* other_entity) override;

private:
    Engine::Image m_block_image;

};

}