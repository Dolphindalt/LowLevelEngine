#ifndef FRAME_GOVERNER_H
#define FRAME_GOVERNER_H

#include "src/containers/pattern/Singleton.h"
#include <SDL2/SDL.h>

class FrameGoverner : public Singleton<FrameGoverner>
{
private:
    const Uint32 fps_target = 60;
    const Uint32 fps_target_ms = 1000 / fps_target;
    Uint32 delta_ms;
    Uint32 end_ms;
    Uint32 begin_ms;

public:
    FrameGoverner();
    ~FrameGoverner();
    
    void tick();
};

#endif