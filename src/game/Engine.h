#ifndef ENGINE_H__
#define ENGINE_H__

#include "src/game/FrameGoverner.h"

class Engine
{
private:
    void mainLoop();
public:
    Engine();
    ~Engine();
};

#endif