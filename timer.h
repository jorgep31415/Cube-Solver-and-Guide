#ifndef timer_h
#define timer_h
#include <chrono>

class Timer
{
public:
    Timer();
    void start();
    double elapsed() const;
    void saveTimeStamp();
    double getTimeStamp() const;
private:
    std::chrono::high_resolution_clock::time_point m_time;
    double m_timeStamp;
};

#endif
