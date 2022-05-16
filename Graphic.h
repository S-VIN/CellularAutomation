#pragma once;
#include <unistd.h>
#include <mutex>

#include "Field.h"
#include "Painter.h"
#include "Automation.h"

void loop()
{
    while (ss.getPause()){}

    Painter& p = Painter::getInstance();
    Automaton a;
    field.clearField();
    field.randomFillField();

    while (p.window.isOpen())
    {
        sf::Event event;
        while (p.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                p.window.close();
        }

        if (!ss.getPause())
        {
            a.automate();
            p.printField(field.getField());
            p.window.display();
            usleep(ss.getTick());
        }

    }
}

void updateDisplay()
{
    Painter& p = Painter::getInstance();
    p.printField(field.getField());
    p.window.display();
}
