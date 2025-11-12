#include "entity/paddle_entity.h"

#include "core/input.h"
#include "entity/entity.h"
#include "graphics/image/image.h"

namespace Breakout {

Paddle::Paddle(float speed, Vector2<float> position, Vector2<int> size)
    : Engine::Entity(position - size.x * .5, size), m_speed(speed),
      m_input_direction(0), m_window_width(0),
      m_paddle_image("assets/images/Paddle.png", m_position, m_size),
      m_collision_shape({0, 0, size.x, size.y}) {
  m_paddle_image.set_color({128, 128, 0}, 255);
}

void Paddle::render(Engine::Window &target_window) {
  m_window_width = target_window.get_window_size().x;

  m_paddle_image.render(target_window);
}

void Paddle::process(float delta_time) {
  Vector2<float> offset = {
      static_cast<float>(m_input_direction) * m_speed * delta_time, 0.0};

  move(offset);
}

void Paddle::handle_event(const SDL_Event &event) {
  Engine::InputManager &input = Engine::InputManager::get_instance();

  m_input_direction = input.get_axis("right", "left"); // already normalized
}

void Paddle::move(const Vector2<float> &offset) {
  Vector2<float> target_position = get_position() + offset;

  const float max_paddle_pos = m_window_width - m_size.x;
  target_position.x = (target_position.x < 0.0) ? 0.0 : target_position.x;
  target_position.x =
      (target_position.x > max_paddle_pos) ? max_paddle_pos : target_position.x;

  set_position(target_position);
}

void Paddle::set_position(const Vector2<float> &position) {
  Engine::Object2D::set_position(position);

  m_paddle_image.set_position(position);
  m_collision_shape.x = position.x;
  m_collision_shape.y = position.y;
}

} // namespace Breakout
