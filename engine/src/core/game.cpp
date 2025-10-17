#include "core/game.h"

#include "math/vector.h"
#include "graphics/image/animated_image.h"


#include "SDL_blendmode.h"
#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include <iostream>
#include <ostream>
#include <string>

Game::Game(const char* title, int window_height, int window_width)
    :m_window(nullptr), m_screen_surface(nullptr), m_is_running(false),
    m_window_height(window_height), m_window_width(window_width)
{
    if (init(title)){
        m_is_running = true;
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
    // images.push_back(
    //     new Image(m_renderer, "../assets/images/sprites.png", Vector2<int>(200, 200), true, Vector3<uint8_t>(0, 255, 255))
    // );

    images.push_back(
        new AnimatedImage(m_renderer, "../assets/images/foo.png", Vector2<int>(64, 205), 4)
    );

    // images.push_back(
    //     new Image("../assets/images/preview.png", m_renderer, Vector3i(0xff, 0xff, 0xff))
    // );
    
    // images[0]->set_size({200, 200});

    // Vector2<int> screen_size = get_screen_surface_size();

    // Image* clip_image = images[0];
    // clip_image->add_image_clip(
    //     {0, 0, 100, 100}, 
    //     {0, 0});
    // clip_image->add_image_clip(
    //     {100, 0, 100, 100}, 
    //     {screen_size.x-100, 0});
    // clip_image->add_image_clip(
    //     {0, 100, 100, 100}, 
    //     {0, screen_size.y - 100});
    // clip_image->add_image_clip(
    //     {100, 100, 100, 100}, 
    //     {screen_size.x - 100, screen_size.y - 100});

    // clip_image->set_color({255, 128, 64}, 128);
    // clip_image->set_blend_mode(SDL_BLENDMODE_BLEND);
}

void Game::process_input()
{
    SDL_Event event;
    if(!SDL_PollEvent(&event)){
        return;
    }

    switch(event.type)
    {
        case SDL_QUIT:
            m_is_running = false;
            break;
    }
}

void Game::update()
{
    // game logic

    // if (!images.empty()){
    //     images[0]->set_size(get_screen_surface_size());
    // }



}

void Game::render()
{
    // drawing
    SDL_RenderClear(m_renderer);

    for (Image* image: images){
        image->render(m_renderer);
    }



    SDL_RenderPresent(m_renderer);
    // SDL_UpdateWindowSurface(m_window);
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

    // m_screen_surface = SDL_GetWindowSurface(m_window);
    // SDL_FillRect(m_screen_surface, NULL, SDL_MapRGB(m_screen_surface->format, 0xff, 0xff, 0xff));
    // SDL_UpdateWindowSurface(m_window);

    m_renderer = SDL_CreateRenderer(m_window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == NULL){
        std::cerr << "Renderer couldn't be created! SDL_Error:" << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetRenderDrawColor(m_renderer, 0xff, 0xff, 0xff, 0xff);

    return true;
}

void Game::clear()
{
    for (Image* image: images){
        delete image;
    }

    SDL_FreeSurface(m_screen_surface);
    SDL_DestroyWindow(m_window);
    m_window = NULL;
    m_screen_surface = NULL;
    SDL_Quit();
}
