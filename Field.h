#pragma once;
#include <SFML/Graphics.hpp>
#include "SettingsStore.h"

using field_t = std::vector<std::vector<sf::RectangleShape>>;


class Field
{
public:
    Field()
    {
        std::vector<sf::RectangleShape> tmp(ss.height.cellQty);
        for (int i = 0; i < ss.width.cellQty; i++)
        {
            field.push_back(tmp);
        }
    }

    void clearField()
    {
        fMutex.lock();
        for (int i = 0; i < ss.width.cellQty; i++)
        {
            for (int j = 0; j < ss.height.cellQty; j++)
            {
                field[i][j].setSize(sf::Vector2f(ss.width.cellSize, ss.height.cellSize));
                field[i][j].setOutlineColor(sf::Color::White);
                field[i][j].setFillColor(sf::Color::Black);
                field[i][j].setOutlineThickness(2);
                field[i][j].setPosition(i * ss.width.cellSize, j * ss.height.cellSize);
            }
        }
        fMutex.unlock();
    }

    void randomFillField()
    {
        fMutex.lock();
        for (auto & row : field)
        {
            for (auto & item : row)
            {
                if (rand() % 100 < ss.probabilityOfRandomBirth)
                {
                    item.setFillColor(sf::Color::White);
                }
                else
                {
                    item.setFillColor(sf::Color::Black);
                }
            }
        }
        fMutex.unlock();
    }

    field_t& getField()
    {
        return field;
    }
private:
    std::mutex fMutex;
    field_t field;
};


Field field;
