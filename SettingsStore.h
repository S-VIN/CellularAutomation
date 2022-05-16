#pragma once;
#include <string>
#include <mutex>

struct Width
{
    int windowSize = 1000;
    int cellQty = 100;
    int cellSize = windowSize / cellQty;
};
struct Height
{
    int windowSize = 1000;
    int cellQty = 100;
    int cellSize = windowSize / cellQty;
};

class SettingsStore
{
private:
    std::mutex ssMutex;
    bool pause = true;
    int tick = 10'000;
public:
    Width width;
    Height height;
    std::string title = "cellular automaton";
    uint8_t probabilityOfRandomBirth = 5;

    bool getPause()
    {
        bool res;
        ssMutex.lock();
        res = pause;
        ssMutex.unlock();
        return res;
    }

    void setPause(bool aPause)
    {
       ssMutex.lock();
       pause = aPause;
       ssMutex.unlock();
    }

    int getTick()
    {
        int res;
        ssMutex.lock();
        res = tick;
        ssMutex.unlock();
        return res;
    }

    void setTick(int aTick)
    {
        ssMutex.lock();
        tick = aTick;
        ssMutex.unlock();
    }

    int getProbability()
    {
        int res;
        ssMutex.lock();
        res = probabilityOfRandomBirth;
        ssMutex.unlock();
        return res;
    }

    void setProbability(int aProbability)
    {
        ssMutex.lock();
        probabilityOfRandomBirth = aProbability;
        ssMutex.unlock();
    }
};

SettingsStore ss;
