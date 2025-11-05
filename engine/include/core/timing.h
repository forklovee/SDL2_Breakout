#pragma once

#include <SDL_stdinc.h>

namespace Engine{

class Timer{
public:
    Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    const Uint32 get_ticks();
    const Uint32 get_ticks_sec();

    const bool& is_started() const;
    const bool is_paused() const;

private:
    Uint32 m_start_ticks;
    Uint32 m_paused_ticks;

    bool m_started;
    bool m_paused;

};


}