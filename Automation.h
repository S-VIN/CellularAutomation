#pragma once
#include "Field.h"

class Automaton
{
public:
    void automate()
    {
        for (int i = 0; i < ss.width.cellQty; i++)
        {
            for (int j = 0; j < ss.height.cellQty; j++)
            {
                if (isAlive(i, j)) field.getField()[i][j].setFillColor(sf::Color::White);
                if (isDie(i, j)) field.getField()[i][j].setFillColor(sf::Color::Black);
            }
        }
    }

private:
    bool isNeighbour(int i, int j)
    {
        return field.getField()[i][j].getFillColor() == sf::Color::White;
    }

    int countNeighbours(int i, int j)
    {
        int res = 0;
        if (i > 0 && isNeighbour(i - 1, j)) res++;
        if (i < ss.width.cellQty - 1 && isNeighbour(i + 1, j)) res++;
        if (j > 0 && isNeighbour(i, j - 1)) res++;
        if (j < ss.height.cellQty - 1 && isNeighbour(i, j + 1)) res++;
        if (i > 0 && j > 0 && isNeighbour(i - 1, j - 1)) res++;
        if (i < ss.width.cellQty - 1 && j < ss.height.cellQty - 1 && isNeighbour(i + 1, j + 1)) res++;
        if (i > 0 && j < ss.height.cellQty - 1 && isNeighbour(i - 1, j + 1)) res++;
        if (i < ss.width.cellQty - 1 && j > 0 && isNeighbour(i + 1, j - 1)) res++;
        return res;
    }

    bool isDie(int i, int j)
    {
        if (countNeighbours(i, j) > 3 || countNeighbours(i, j) < 2)
            return true;
        return false;
    }

    bool isAlive(int i, int j)
    {
        if (countNeighbours(i, j) == 3)
            return true;
        return false;
    }
};
