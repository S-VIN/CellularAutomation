#pragma once;
#include <SFML/Graphics.hpp>
#include "Field.h"
class Painter
{
public:
    static Painter& getInstance()
    {
        static Painter instance;
        return instance;
    }

    void printField(const field_t aField)
    {
        pMutex.lock();
        for (const auto & row : aField)
        {
            for (const auto & item : row)
            {
                window.draw(item);
            }
        }
        pMutex.unlock();
    }
    sf::RenderWindow window{sf::VideoMode(ss.width.windowSize, ss.height.windowSize), ss.title};
    Painter(Painter const&) = delete;
    void operator=(Painter const&)  = delete;

private:
    std::mutex pMutex;
    Painter() {}


};