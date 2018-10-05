#include "timer.h"

Timer::Timer()
{
    start();
}

void Timer::start()
{
    m_time = std::chrono::high_resolution_clock::now();
}

void Timer::saveTimeStamp()
{
    std::chrono::duration<double,std::milli> diff =
    std::chrono::high_resolution_clock::now() - m_time;
    m_timeStamp = diff.count() / 1000;
}

double Timer::getTimeStamp() const
{
    return m_timeStamp;
}

double Timer::elapsed() const
{
    std::chrono::duration<double,std::milli> diff =
    std::chrono::high_resolution_clock::now() - m_time;
    return diff.count();
}
