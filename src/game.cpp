#include "game.h"

#include "software_image.h"
#include "vector.h"
#include <ostream>

Game::Game(const char* title, int window_height, int window_width)
    :m_window(nullptr), m_screen_surface(nullptr), m_is_running(false),
    m_window_height(window_height), m_window_width(window_width)
{
    if (init(title)){
        m_is_running = true;

    }
}

Game::~Game()
{
}

void Game::run()
{
    start();

    while(m_is_running){
        process_input();
        update();
        render();
    }
}

Vector2i Game::get_screen_surface_size() const
{
    if (!m_screen_surface){
        return {};
    }
    return {400, 800};
}

void Game::start()
{
    images.push_back(
        new SoftwareImage("../assets/images/preview.bmp", m_screen_surface)
    );
}

void Game::process_input()
{
    SDL_Event event;
    if(!SDL_PollEvent(&event)){
        return;
    }

    std::cout << "Event processing." << std::endl;

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

    if (!images.empty()){
        images[0]->set_size(get_screen_surface_size());
        images[0]->draw(m_screen_surface);
    }

    
}

void Game::render()
{
    // drawing

    SDL_UpdateWindowSurface(m_window);
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

    m_screen_surface = SDL_GetWindowSurface(m_window);
    SDL_FillRect(m_screen_surface, NULL, SDL_MapRGB(m_screen_surface->format, 0xff, 0xff, 0xff));

    SDL_UpdateWindowSurface(m_window);

    return true;
}

void Game::clear()
{
    for (SoftwareImage* image: images){
        free(image);
    }

    SDL_FreeSurface(m_screen_surface);
    SDL_DestroyWindow(m_window);
    m_window = NULL;
    m_screen_surface = NULL;
    SDL_Quit();
}
