#include "core/timing.h"
#include <SDL_timer.h>

namespace Engine {

Timer::Timer()
    :m_started(false), m_paused(false), m_start_ticks(0), m_paused_ticks(0)
{

}

void Timer::start(){
    m_started = true;
    m_paused = false;

    m_start_ticks = SDL_GetTicks();
    m_paused_ticks = 0;
}

void Timer::stop(){
    m_started = false;
    m_paused = false;

    m_start_ticks = 0;
    m_paused_ticks = 0;
}

void Timer::pause(){
    if (m_started && !m_paused){
        m_paused = true;

        m_paused_ticks = SDL_GetTicks() - m_start_ticks;
        m_start_ticks = 0;
    }
}

void Timer::unpause(){
    if (m_started && m_paused){
        m_paused = false;

        m_start_ticks = SDL_GetTicks() - m_paused_ticks;
        m_paused_ticks = 0;
    }
}

const Uint32 Timer::get_ticks(){
    if (m_started){
        return is_paused() ? m_paused_ticks : SDL_GetTicks() - m_start_ticks;
    }
    return 0;
}

const float Timer::get_ticks_sec(){
    return get_ticks() / 1000.f;
}

const bool& Timer::is_started() const{
    return m_started;
}
const bool Timer::is_paused() const{
    return m_paused && m_started;
}

}