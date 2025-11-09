#include "core/window.h"

#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <iostream>

namespace Engine{

Window::Window(std::string window_name, Vector2<int> size, Vector2<int> position)
    :m_name(window_name), m_window_transform({position.x, position.y, size.x, size.y})
{
    // Create SDL window
    m_window = SDL_CreateWindow(window_name.c_str(),
        m_window_transform.x, m_window_transform.y,
        m_window_transform.w, m_window_transform.h, 
        SDL_WINDOW_SHOWN);
    
    if (m_window == NULL){
        std::cerr << "Window couldn't be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == NULL){
        std::cerr << "Renderer couldn't be created! SDL_Error:" << SDL_GetError() << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(m_renderer, 0xff, 0xff, 0xff, 0xff);
}

Window::~Window(){
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    
    std::cout << "Window destroyed!\n";
}

SDL_Renderer* Window::get_renderer() const{
    return m_renderer;
}

void Window::clear_renderer() const{
    SDL_RenderClear(m_renderer);
}
void Window::update_renderer() const{
    SDL_RenderPresent(m_renderer);
}


const SDL_Rect& Window::get_window_transform() const{
    return m_window_transform;
}

Vector2<int> Window::get_window_position() const{
    return {m_window_transform.x, m_window_transform.y};
}

Vector2<int> Window::get_window_size() const{
    return {m_window_transform.w, m_window_transform.h};
}






}