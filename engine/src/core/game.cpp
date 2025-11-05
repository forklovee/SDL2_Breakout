#include "core/game.h"

#include "core/input.h"
#include "graphics/image/image.h"
#include "graphics/image/text_image.h"
#include "math/vector.h"
#include "graphics/image/animated_image.h"

#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include "ui/button/button.h"
#include <SDL_keycode.h>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

namespace Engine {

InputManager& input = InputManager::get_instance();
TTF_Font* default_font = nullptr;

Game::Game(const char* title, int window_height, int window_width)
    :m_window(nullptr), m_screen_surface(nullptr), m_is_running(false),
    m_window_height(window_height), m_window_width(window_width),
    m_timer(Timer()), m_counted_frames(0)
{
    if (init(title)){
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
    std::cout << "Game started in " << get_screen_surface_size() << " window." << std::endl;

    start();

    while(m_is_running){
        process_input();
        update();
        render();
    }
}

Vector2<int> Game::get_screen_surface_size() const
{
    return {m_window_width, m_window_height};
}

void Game::start()
{
    input.bind_action("up", SDLK_w);    
    input.bind_action("down", SDLK_s);
    input.bind_action("left", SDLK_a);
    input.bind_action("right", SDLK_d);

    Engine::default_font = TTF_OpenFont("../assets/fonts/Proto/0xProtoNerdFontPropo-Regular.ttf", 9);
    if (default_font == NULL){
        std::cerr << "Default font not loaded :(" << std::endl;
    }


    TTF_Font* font = TTF_OpenFont("../assets/fonts/Proto/0xProtoNerdFontPropo-Regular.ttf", 28);
    if (font == NULL){
        std::cerr << "Font not loaded :(" << std::endl;
    }
    fonts.push_back(font);


    TextImage* text_image = new TextImage(m_renderer, "Hello, world!", fonts[0], {}, Vector2<int>{100, 20}, Vector3<uint8_t>{0}, 255);
    Image* image = new Image(m_renderer, "../assets/images/preview.png", {100}, {200, 150});
    AnimatedImage* animated_image = new AnimatedImage(m_renderer, "../assets/images/foo.png", {200, 400}, {64, 205}, 4);

    objects.push_back(animated_image);
    objects.push_back(image);
    objects.push_back(text_image);

    Button* button = new Button(m_renderer, "Button!", true, {200, 64});
    objects.push_back(button);

}

void Game::process_input()
{
    SDL_Event& event = input.update();
    m_is_running = !input.is_quit_requested();
    
    for (Object2D* object: objects){
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
    TextImage* text_image = dynamic_cast<TextImage*>(objects[2]);
    text_image->set_text(delta_text.str());
    
    Object2D* object_ptr = objects[0];
    Vector2<int> direction = input.get_vector("right", "left", "down", "up");
    if (object_ptr){
        object_ptr->set_position(object_ptr->get_position() + direction);
    }

    // if (!images.empty()){
    //     images[0]->set_size(get_screen_surface_size());
    // }


}

void Game::render()
{
    // drawing
    SDL_RenderClear(m_renderer);

    for (Object2D* object: objects){
        object->render(m_renderer);
    }

    SDL_RenderPresent(m_renderer);
    ++m_counted_frames;
}

bool Game::init(const char* title)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL couldn't initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_window = SDL_CreateWindow(title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        m_window_width, m_window_height, 
        SDL_WINDOW_SHOWN);
    
    if (m_window == NULL){
        std::cerr << "Window couldn't be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    int img_init_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP;
    if (!(IMG_Init(img_init_flags) & IMG_INIT_PNG)){
        std::cerr << "SDL_Image couldn't initialize PNG loader! SDL_Image_Error: " << IMG_GetError() << std::endl;
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == NULL){
        std::cerr << "Renderer couldn't be created! SDL_Error:" << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetRenderDrawColor(m_renderer, 0xff, 0xff, 0xff, 0xff);

    if (TTF_Init() < 0)
    {
        std::cerr << "SDL_ttf couldn't initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

void Game::clear()
{
    for (Object2D* object: objects)
    {
        delete object;
    }

    TTF_CloseFont(Engine::default_font);
    for (TTF_Font* font_ptr: fonts)
    {
        TTF_CloseFont(font_ptr);
    }

    SDL_FreeSurface(m_screen_surface);
    SDL_DestroyWindow(m_window);
    m_window = NULL;
    m_screen_surface = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

}