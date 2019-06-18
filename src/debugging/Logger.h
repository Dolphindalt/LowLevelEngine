#ifndef LOGGER_H
#define LOGGER_H

class Logger
{
private:

public:
    void init();
    void destroy();
    void logWarning(const char *warning, const char *file, unsigned int line);
};

#endif