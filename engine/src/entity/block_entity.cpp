#include "entity/block_entity.h"
#include "entity/ball_entity.h"
#include "entity/entity.h"

namespace Breakout {

BlockEntity::BlockEntity(Vector2<float> position, Vector2<int> size)
    : Engine::Entity(position, size),
      m_block_image("assets/images/preview.png", position, size) {
  m_block_image.set_color({64}, 255);
}

void BlockEntity::render(Engine::Window& target_window){
  m_block_image.render(target_window);
}


void BlockEntity::set_color(Vector3<uint8_t> color, uint8_t alpha) {
  m_block_image.set_color(color, alpha);
}

void BlockEntity::on_collision(Entity *other_entity) {
  Engine::Entity::on_collision(other_entity);

  if (dynamic_cast<BallEntity *>(other_entity)) {
    destroy();
  }
}

} // namespace Breakout
