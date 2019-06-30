#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
class Singleton
{
public:
    static T &getInstance()
    {
        static T instance; // will be destroyed
        return instance; // instantiated on first use
    }
    Singleton(Singleton const &) = delete;
    void operator=(Singleton const &) = delete;
protected:
    Singleton() {}
};

#endif