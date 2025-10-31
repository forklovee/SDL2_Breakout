#include "core/input.h"
#include <SDL_events.h>
#include <SDL_stdinc.h>

#include <iostream>

namespace Engine {

SDL_Event& InputManager::update() {
  m_last_key_states = m_key_states;
  m_last_mouse_states = m_mouse_states;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      m_quit_requested = true;
      break;
    case SDL_KEYDOWN:
      m_key_states[event.key.keysym.sym] = true;
      break;
    case SDL_KEYUP:
      m_key_states[event.key.keysym.sym] = false;
      break;
    case SDL_MOUSEBUTTONDOWN:
      m_mouse_states[event.button.button] = true;
      break;
    case SDL_MOUSEBUTTONUP:
      m_mouse_states[event.button.button] = false;
      break;
    case SDL_MOUSEMOTION:
      m_mouse_position.x = event.motion.x;
      m_mouse_position.y = event.motion.y;
    }
  }

  return event;
}

void InputManager::bind_action(const std::string& action_name, SDL_Keycode keycode) {
  if (m_action_bindings.contains(action_name)){
    std::cerr << "InputManager: Action '" << action_name << "' is already bound to a key. Overwriting binding.\n";
    return;
  }
  m_action_bindings[action_name] = keycode;
}

void InputManager::unbind_action(const std::string &action_name){
  if (!m_action_bindings.contains(action_name)){
    std::cerr << "InputManager: Action '" << action_name << "' couldn't be unbind. Not found.\n";
    return;
  }
  m_action_bindings.erase(action_name);
}

bool InputManager::is_quit_requested(){
  return m_quit_requested;
}

bool InputManager::is_action_pressed(const std::string& action_name){
  if (!m_action_bindings.contains(action_name)){
    return false;
  }
  const SDL_Keycode& keycode = m_action_bindings.at(action_name);
  if (!m_key_states.contains(keycode)){
    return false;
  }
  return m_key_states.at(keycode);
}

bool InputManager::is_action_just_pressed(const std::string& action_name){
  if (!m_action_bindings.contains(action_name)){
    return false;
  }
  const SDL_Keycode& keycode = m_action_bindings.at(action_name);
  if (!m_key_states.contains(keycode) || !m_last_key_states.contains(keycode)){
    return false;
  }
  return !m_key_states.at(keycode) && m_last_key_states.at(keycode);
}

bool InputManager::is_action_released(const std::string& action_name){
  if (!m_action_bindings.contains(action_name)){
    return false;
  }
  const SDL_Keycode& keycode = m_action_bindings.at(action_name);
  if (!m_key_states.contains(keycode)){
    return false;
  }
  return !m_key_states.at(keycode);
}

bool InputManager::is_action_just_released(const std::string& action_name){
  if (!m_action_bindings.contains(action_name)){
    return false;
  }

  const SDL_Keycode& keycode = m_action_bindings.at(action_name);
  if (!m_key_states.contains(keycode) || !m_last_key_states.contains(keycode)){
    return false;
  }

  return !m_key_states.at(keycode) && m_last_key_states.at(keycode);
}

Vector2<int32_t>& InputManager::get_mouse_position(){
  return m_mouse_position;
}

bool InputManager::is_mouse_button_pressed(bool secondary){
  const Uint8 target_button = secondary ? 3 : 1;
  if (!m_mouse_states.contains(target_button)){
    return false;
  }
  return m_mouse_states.at(target_button);
}

bool InputManager::is_mouse_button_just_pressed(bool secondary){
  const Uint8 target_button = secondary ? 3 : 1;
  if (!m_mouse_states.contains(target_button) || !m_last_mouse_states.contains(target_button)){
    return false;
  }

  return m_mouse_states.at(target_button) && !m_last_key_states.at(target_button);
}

bool InputManager::is_mouse_button_released(bool secondary){
  const Uint8 target_button = secondary ? 3 : 1;
  if (!m_mouse_states.contains(target_button)){
    return false;
  }
  return !m_mouse_states.at(target_button);
}

bool InputManager::is_mouse_button_just_released(bool secondary){
  const Uint8 target_button = secondary ? 3 : 1;
  if (!m_mouse_states.contains(target_button) || !m_last_mouse_states.contains(target_button)){
    return false;
  }

  return m_mouse_states.at(target_button) && !m_last_key_states.at(target_button);
}



} // namespace Engine
