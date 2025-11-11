#include "core/game.h"

#include "core/input.h"
#include "core/window.h"
#include "entity/ball_entity.h"
#include "entity/block_entity.h"
#include "entity/entity.h"
#include "entity/paddle_entity.h"
#include "graphics/object2d.h"
#include "math/vector.h"

#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_image.h"
#include <SDL_keycode.h>
#include <SDL_stdinc.h>
#include <SDL_ttf.h>
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace Engine {

InputManager &input = InputManager::get_instance();
TTF_Font *default_font = nullptr;

Game::Game(const char *title, int window_height, int window_width)
    : m_is_running(false), m_timer(Timer()), m_counted_frames(0),
      m_cap_timer(Timer()), m_fps_cap_enabled(true), m_fps_cap(60) {
  if (init(title, {window_width, window_height})) {
    m_is_running = true;
    m_timer.start();
  } else {
    std::string input_wait_line_dummy;
    std::getline(std::cin, input_wait_line_dummy);
  }
}

Game::~Game() { clear(); }

void Game::run() {
  start();

  while (m_is_running) {
    m_cap_timer.start();

    process_input();
    update();
    render();

    for (auto& object: m_objects){
      if (object && object->is_valid()){
        continue;
      }
      remove_object(object.get());
    }

    for (auto& entity: m_entities){
      if (entity && entity->is_valid()){
        continue;
      }
      remove_entity(entity.get());
    }

    m_step_timer.start();

    if (const int frame_ticks = m_cap_timer.get_ticks(); m_fps_cap_enabled) {
      // frame finished early, wait!
      if (frame_ticks < get_screen_ticks_per_frame()) {
        SDL_Delay(get_screen_ticks_per_frame() - frame_ticks);
      }
    }
  }
}

const Window &Game::create_window(std::string name, Vector2<int> size,
                                  Vector2<int> position) {
  Window *new_window = new Window(name, size, position);
  return *new_window;
}

void Game::set_fps_cap_enabled(bool state) {
  m_fps_cap_enabled = state;
  if (!m_fps_cap_enabled) {
    m_cap_timer.stop();
  }
}

const bool &Game::get_fps_cap_enabled() const { return m_fps_cap_enabled; }

void Game::set_fps_cap(uint16_t fps_cap) { m_fps_cap = fps_cap; }

const uint16_t &Game::get_fps_cap() const { return m_fps_cap; }

const int Game::get_screen_ticks_per_frame() { return 1000 / get_fps_cap(); }

Object2D *Game::register_object(const std::string &name,
                                std::unique_ptr<Object2D> &&object_2d_ptr) {
  Object2D *raw_object_ptr = object_2d_ptr.get();
  m_objects.push_back(std::move(object_2d_ptr));
  m_object_lookup_map.emplace(name, raw_object_ptr);
  return raw_object_ptr;
}

void Game::remove_object(const std::string &name) {
  auto object_map_it = m_object_lookup_map.find(name);
  if (object_map_it == m_object_lookup_map.end()) {
    return; // object of name not found.
  }

  Object2D *object_ptr = object_map_it->second;

  // remove unique_ptr from vector -> Destroy the object.
  m_objects.erase(std::remove_if(
      m_objects.begin(), m_objects.begin(),
      [object_ptr](const auto &o) { return o.get() == object_ptr; }));

  // remove from lookup map
  m_object_lookup_map.erase(object_map_it);
}

void Game::remove_object(Object2D* object_2d_ptr){
  const auto& object_pair = std::find_if(
    m_object_lookup_map.begin(), m_object_lookup_map.end(),
    [object_2d_ptr](const auto& object_pair) { return object_2d_ptr == object_pair.second; });
  
  if (object_pair != m_object_lookup_map.end()){
    m_object_lookup_map.erase(object_pair);
  }
  
  const auto& object = std::find_if(
    m_objects.begin(), m_objects.end(),
    [object_2d_ptr](const auto& object_2d) { return object_2d_ptr == object_2d.get(); });
  
  if (object != m_objects.end()){
    m_objects.erase(object);
  }

}


Entity *Game::register_entity(const std::string &name,
                              std::unique_ptr<Entity> &&entity_ptr) {
  Entity *raw_entity_ptr = entity_ptr.get();
  m_entities.push_back(std::move(entity_ptr));
  m_entity_lookup_map.emplace(name, raw_entity_ptr);
  return raw_entity_ptr;
}

void Game::remove_entity(const std::string &name) {
  auto entity_map_it = m_entity_lookup_map.find(name);
  if (entity_map_it == m_entity_lookup_map.end()) {
    return; // object of name not found.
  }

  Entity *entity_ptr = entity_map_it->second;

  // remove unique_ptr from vector -> Destroy the object.
  m_entities.erase(std::remove_if(
      m_entities.begin(), m_entities.begin(),
      [entity_ptr](const auto &e) { return e.get() == entity_ptr; }));

  // remove from lookup map
  m_entity_lookup_map.erase(entity_map_it);
}

void Game::remove_entity(Entity* entity_ptr){
  const auto& entity_pair = std::find_if(
    m_entity_lookup_map.begin(), m_entity_lookup_map.end(),
    [entity_ptr](const auto& entity_pair) { return entity_ptr == entity_pair.second; });
  
  if (entity_pair != m_entity_lookup_map.end()){
    m_entity_lookup_map.erase(entity_pair);
  }
  
  const auto& entity = std::find_if(
    m_entities.begin(), m_entities.end(),
    [entity_ptr](const auto& entity) { return entity_ptr == entity.get(); });
  
  if (entity != m_entities.end()){
    m_entities.erase(entity);
  }
}



void Game::start() {
  std::cout << "Game started in directory: " << std::filesystem::current_path()
            << "\n";

  input.bind_action("left", SDLK_a);
  input.bind_action("right", SDLK_d);

  Engine::default_font =
      TTF_OpenFont("assets/fonts/Proto/0xProtoNerdFontPropo-Regular.ttf", 9);
  if (default_font == NULL) {
    std::cerr << "Default font not loaded: " << TTF_GetError() << std::endl;
  }

  TTF_Font *font =
      TTF_OpenFont("assets/fonts/Proto/0xProtoNerdFontPropo-Regular.ttf", 28);
  if (font == NULL) {
    std::cerr << "Font not loaded: " << TTF_GetError() << std::endl;
  }
  fonts.push_back(font);

  const Vector2<int> window_size = m_main_window->get_window_size();
  const Vector2<float> paddle_pos = {static_cast<float>(window_size.x) / 2.f,
                                     static_cast<float>(window_size.y) - 50.f};

  for (size_t row{0}; row < 4; row++) {
    for (size_t col{0}; col < 3; col++) {
      size_t block_id = col + row * 4;
      std::string block_name = "block" + std::to_string(block_id);

      Vector2<float> block_position = {
        col * 128.f,
        row * 68.f};

      std::unique_ptr<Breakout::BlockEntity> block =
          std::make_unique<Breakout::BlockEntity>(block_position);
      // block->set_color({128}, 255);
      register_entity(block_name, std::move(block));
    }
  }

  register_entity("Ball", std::make_unique<Breakout::BallEntity>(
                              200.f, Vector2<float>{100, 400}));
  ball = dynamic_cast<Breakout::BallEntity *>(m_entity_lookup_map.at("Ball"));

  register_entity("Paddle",
                  std::make_unique<Breakout::Paddle>(100.f, paddle_pos));
  paddle = dynamic_cast<Breakout::Paddle *>(m_entity_lookup_map.at("Paddle"));
}

void Game::process_input() {
  SDL_Event &event = input.update();
  m_is_running = !input.is_quit_requested();

  paddle->handle_event(event);

  for (const auto &object : m_objects) {
    object->handle_event(event);
  }
}

void Game::update() {
  // game logic
  float avg_fps = m_counted_frames / m_timer.get_ticks_sec();
  if (avg_fps > 2000000) {
    avg_fps = 0;
  }

  std::stringstream delta_text{""};
  delta_text << "Avg FPS: " << avg_fps;

  float delta_time = m_step_timer.get_ticks_sec();

  ball->physics_process(delta_time, m_entities);
  ball->process(delta_time);

  for (auto &entity : m_entities) {
    if (!entity){
      continue;
    }
    entity->process(delta_time);
  }

  for (auto &object : m_objects) {
    if (!object){
      continue;
    }
    object->process(delta_time);
  }
}

void Game::render() {
  // drawing
  m_main_window->clear_renderer();

  for (auto &entity : m_entities) {
    if (!entity->is_visible() || !entity) {
      continue;
    }
    entity->render(*m_main_window.get());
  }

  for (auto &object : m_objects) {
    if (!object->is_visible() || !object)
      continue;
    object->render(*m_main_window.get());
  }

  m_main_window->update_renderer();
  ++m_counted_frames;
}

bool Game::init(const char *title, Vector2<int> size) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL couldn't initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  int img_init_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP;
  if (!(IMG_Init(img_init_flags) & IMG_INIT_PNG)) {
    std::cerr << "SDL_Image couldn't initialize PNG loader! SDL_Image_Error: "
              << IMG_GetError() << std::endl;
    return false;
  }

  if (TTF_Init() < 0) {
    std::cerr << "SDL_ttf couldn't initialize! TTF_Error: " << TTF_GetError()
              << std::endl;
    return false;
  }

  m_main_window = std::make_unique<Window>(title, size);

  return true;
}

void Game::clear() {
  TTF_CloseFont(Engine::default_font);
  for (TTF_Font *font_ptr : fonts) {
    TTF_CloseFont(font_ptr);
  }

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

} // namespace Engine
