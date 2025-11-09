#include "core/game.h"

#include "core/input.h"
#include "core/window.h"
#include "entity/ball_entity.h"
#include "entity/paddle_entity.h"
#include "graphics/image/image.h"
#include "graphics/image/text_image.h"
#include "graphics/object2d.h"
#include "math/vector.h"
#include "graphics/image/animated_image.h"

#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_image.h"
#include "ui/button/button.h"
#include <SDL_keycode.h>
#include <SDL_stdinc.h>
#include <SDL_ttf.h>
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace Engine {

InputManager& input = InputManager::get_instance();
TTF_Font* default_font = nullptr;

Game::Game(const char* title, int window_height, int window_width)
    :m_is_running(false),
    m_timer(Timer()), m_counted_frames(0), 
    m_cap_timer(Timer()), m_fps_cap_enabled(true), m_fps_cap(60)
{
    if (init(title, {window_width, window_height})){
        m_is_running = true;
        m_timer.start();
    }
    else{
        std::string input_wait_line_dummy;
        std::getline(std::cin, input_wait_line_dummy);
    }
}

Game::~Game()
{
    clear();
}

void Game::run()
{
    start();

    while(m_is_running){
        m_cap_timer.start();

        process_input();
        update();
        render();

        m_step_timer.start();

        if (const int frame_ticks = m_cap_timer.get_ticks(); m_fps_cap_enabled){
            // frame finished early, wait!
            if (frame_ticks < get_screen_ticks_per_frame()){
                SDL_Delay(get_screen_ticks_per_frame() - frame_ticks);
            }
        }
    }
}

const Window& Game::create_window(std::string name, Vector2<int> size, Vector2<int> position){
    Window* new_window = new Window(name, size, position);
    return *new_window;
}

void Game::set_fps_cap_enabled(bool state){
    m_fps_cap_enabled = state;
    if (!m_fps_cap_enabled) {
        m_cap_timer.stop();
    }
}

const bool& Game::get_fps_cap_enabled() const{
    return m_fps_cap_enabled;
}

void Game::set_fps_cap(uint16_t fps_cap){
    m_fps_cap = fps_cap;
}

const uint16_t& Game::get_fps_cap() const{
    return m_fps_cap;
}

const int Game::get_screen_ticks_per_frame() {
    return 1000 / get_fps_cap();
}


void Game::register_object(std::string object_name, Object2D* object_2d_ptr){
    
    for(std::string new_object_name = object_name; m_objects.find(object_name) != m_objects.end();){
        std::cout << "Bajo " << new_object_name << "\n";
    }

    std::unique_ptr<Object2D> object_2d = std::unique_ptr<Object2D>(object_2d_ptr);
    m_objects.insert(std::make_pair(object_name, std::move(object_2d)));
}

void Game::destroy_object(std::string object_name){
    if (m_objects.find(object_name) == m_objects.end()){
        return;
    }
    m_objects.erase(object_name);
    std::unique_ptr<Object2D>& object2d = m_objects.at(object_name);
    object2d.reset();
}


Object2D* Game::get_object(std::string object_name){
    if (m_objects.find(object_name) == m_objects.end()){
        return nullptr;
    }
    Object2D* object2d = m_objects[object_name].get();
    return object2d;
}

void Game::on_object_destroyed(Object2D* object){
    auto object_pair = std::find_if(
        m_objects.begin(), m_objects.end(),
        [&] (std::pair<const std::string, std::unique_ptr<Object2D>>& pair){
            return pair.second.get() == object;
        });
    
    if (object_pair == m_objects.end()){
        return;
    }
    m_objects.erase(object_pair->first);
}


const std::vector<Object2D*> Game::get_all_objects(){
    std::vector<Object2D*> all_objects{};
    for(auto& object_pair: m_objects){
        Object2D* object_raw_ptr = object_pair.second.get();
        all_objects.push_back(object_raw_ptr);
    }
    return all_objects;
}



void Game::start()
{
    std::cout << "Game started in directory: " << std::filesystem::current_path() << "\n";

    input.bind_action("up", SDLK_w);    
    input.bind_action("down", SDLK_s);
    input.bind_action("left", SDLK_a);
    input.bind_action("right", SDLK_d);

    Engine::default_font = TTF_OpenFont("assets/fonts/Proto/0xProtoNerdFontPropo-Regular.ttf", 9);
    if (default_font == NULL){
        std::cerr << "Default font not loaded: " << TTF_GetError() << std::endl;
    }

    TTF_Font* font = TTF_OpenFont("assets/fonts/Proto/0xProtoNerdFontPropo-Regular.ttf", 28);
    if (font == NULL){
        std::cerr << "Font not loaded: " << TTF_GetError() << std::endl;
    }
    fonts.push_back(font);


    register_object("HelloText",
        new TextImage("Hello, world!", fonts[0], Vector2<float>{}, Vector2<int>{100, 20}, Vector3<uint8_t>{0}, 255)
    );
        
    register_object("Preview",
        new Image("assets/images/preview.png", {100}, {200, 150}));
    register_object("Animation",
        new AnimatedImage("assets/images/foo.png", {200, 400}, {64, 205}, 4));


    register_object("Button",
        new Button("Button!", true, {64, 64}));

    register_object("Ball",
         new Breakout::BallEntity(Vector2<float>{100, 400})
    );

    Vector2<int> window_size = m_main_window->get_window_size();
    Vector2<float> paddle_pos = {
         static_cast<float>(window_size.x)/2.f,
         static_cast<float>(window_size.y) - 50.f
    };
    
    register_object("Paddle", new Breakout::Paddle(paddle_pos));
}

void Game::process_input()
{
    SDL_Event& event = input.update();
    m_is_running = !input.is_quit_requested();
    
    for (Object2D* object: get_all_objects()){
        object->handle_event(event);
    }
}

void Game::update()
{
    // game logic
    float avg_fps = m_counted_frames / m_timer.get_ticks_sec();
    if (avg_fps > 2000000){
        avg_fps = 0;
    }

    std::stringstream delta_text{""};
    delta_text << "Avg FPS: " << avg_fps;
    TextImage* text_image = dynamic_cast<TextImage*>(get_object("HelloText"));
    text_image->set_text(delta_text.str());

    float delta_time = m_step_timer.get_ticks_sec();
    for (Object2D* object: get_all_objects()){
        object->process(delta_time);
    }

}

void Game::render()
{
    // drawing
    m_main_window->clear_renderer();

    for (Object2D* object: get_all_objects()){
        object->render(*m_main_window.get());
    }

    m_main_window->update_renderer();
    ++m_counted_frames;
}

bool Game::init(const char* title, Vector2<int> size)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL couldn't initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    int img_init_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP;
    if (!(IMG_Init(img_init_flags) & IMG_INIT_PNG)){
        std::cerr << "SDL_Image couldn't initialize PNG loader! SDL_Image_Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() < 0)
    {
        std::cerr << "SDL_ttf couldn't initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    m_main_window = std::make_unique<Window>(title, size);
    
    return true;
}

void Game::clear()
{
    TTF_CloseFont(Engine::default_font);
    for (TTF_Font* font_ptr: fonts)
    {
        TTF_CloseFont(font_ptr);
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

}