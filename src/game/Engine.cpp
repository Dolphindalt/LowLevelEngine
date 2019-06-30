#include "src/game/Engine.h"

Engine::Engine()
{

}

Engine::~Engine()
{

}

void Engine::mainLoop()
{
    while(true)
    {
        // Calcluate frame delta and appropraite delay
        FrameGoverner::getInstance().tick();
    }
}