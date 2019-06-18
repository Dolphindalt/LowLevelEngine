#include "src/debugging/Logger.h"

static Logger logger;

#ifndef TEST_BUILD

int main() 
{
    logger.init();
    logger.logWarning("The logging system is working", __FILE__, __LINE__);
    logger.destroy();
}

#endif