#pragma once

#include "core/timing.h"
#include "core/window.h"
#include "entity/ball_entity.h"
#include "entity/entity.h"
#include "entity/paddle_entity.h"
#include "graphics/object2d.h"
#include "math/vector.h"

#include <SDL_ttf.h>
#include <memory>
#include <string_view>
#include <unordered_map>
#include <string>
#include <vector>

namespace Engine{

class Image;
class Button;

static const char* ASSET_PATH = "../game/assets/";
extern TTF_Font* default_font;

// extern const TTF_Font* default_font;

class Game{

public:
    Game(const char* title, int window_height, int window_width);
    ~Game();

    void run();

#pragma region Window

    const Window& create_window(std::string name, Vector2<int> size, Vector2<int> position);

#pragma endregion Window

#pragma region FPS

    void set_fps_cap_enabled(bool state);
    const bool& get_fps_cap_enabled() const;
    
    void set_fps_cap(uint16_t fps_cap);
    const uint16_t& get_fps_cap() const;

#pragma endregion FPS

    Object2D* register_object(const std::string& name, std::unique_ptr<Object2D>&& object_2d_ptr);
    void remove_object(const std::string& name);
    
    Entity* register_entity(const std::string& name, std::unique_ptr<Entity>&& entity_ptr);
    void remove_entity(const std::string& name);

private:
    void start();

    void process_input();
    void update();
    void render();

    bool init(const char* title, Vector2<int> size);
    void clear();

    const int get_screen_ticks_per_frame();

private:
    bool m_is_running;
    std::unique_ptr<Window> m_main_window;

    Timer m_timer;
    uint32_t m_counted_frames;

    Timer m_step_timer;

    bool m_fps_cap_enabled;
    Timer m_cap_timer;
    uint16_t m_fps_cap;

    Breakout::BallEntity* ball;
    Breakout::Paddle* paddle;

    std::vector<TTF_Font*> fonts;

    std::vector<std::unique_ptr<Object2D>> m_objects;
    std::unordered_map<std::string, Object2D*> m_object_lookup_map;

    std::vector<std::unique_ptr<Entity>> m_entities;
    std::unordered_map<std::string, Entity*> m_entity_lookup_map;

};

}
