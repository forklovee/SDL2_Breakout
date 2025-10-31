#pragma once

#include "math/vector.h"
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <cstdint>
#include <unordered_map>

namespace Engine {

class InputManager {
public:
  static InputManager& get_instance() {
    static InputManager instance;
    return instance;
  }

  InputManager(const InputManager &) = delete;
  InputManager &operator=(const InputManager &) = delete;

  SDL_Event& update();

  void bind_action(const std::string &action_name, SDL_Keycode keycode);
  void unbind_action(const std::string &action_name);

  bool is_quit_requested();

  bool is_action_pressed(const std::string& action_name);
  bool is_action_just_pressed(const std::string& action_name);
  bool is_action_released(const std::string& action_name);
  bool is_action_just_released(const std::string& action_name);

  Vector2<int32_t>& get_mouse_position();
  bool is_mouse_button_pressed(bool secondary = false);  
  bool is_mouse_button_just_pressed(bool secondary = false);
  bool is_mouse_button_released(bool secondary = false);
  bool is_mouse_button_just_released(bool secondary = false);

  const Vector2<int> get_vector(const std::string& x_axis_pos_action, const std::string& x_axis_neg_action,
    const std::string& y_axis_pos_action, const std::string& y_axis_neg_action);

private:
  InputManager() : m_quit_requested(false), m_mouse_position({}) {}

private:
  SDL_Event event;

  std::unordered_map<std::string, SDL_Keycode> m_action_bindings;

  std::unordered_map<SDL_Keycode, bool> m_key_states;
  std::unordered_map<SDL_Keycode, bool> m_last_key_states;
  
  std::unordered_map<uint8_t, bool> m_mouse_states;
  std::unordered_map<uint8_t, bool> m_last_mouse_states;
  Vector2<int32_t> m_mouse_position;

  bool m_quit_requested;
};

} // namespace Engine
