#include "src/game/FrameGoverner.h"

FrameGoverner::FrameGoverner()
: Singleton<FrameGoverner>()
{
    begin_ms = SDL_GetTicks();
}

FrameGoverner::~FrameGoverner()
{

}

void FrameGoverner::tick()
{
    end_ms = SDL_GetTicks();
    delta_ms = begin_ms - end_ms;
    if(delta_ms < fps_target_ms)
    {
        // wait the rest of the frame
        SDL_Delay(delta_ms);
    }
    else if(delta_ms > fps_target_ms)
    {
        // wait an entire frame
        SDL_Delay(fps_target_ms);
    }
    begin_ms = SDL_GetTicks();
}