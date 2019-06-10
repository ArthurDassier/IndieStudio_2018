/*
** EPITECH PROJECT, 2019
** clock
** File description:
** clock
*/

#include "client/Clock.hpp"

Clock::Clock():
    _clock(),
    _second(70000000LL)
{
}

Clock::~Clock()
{

}

void Clock::setElapsedTime()
{
    _elapsed_times = _clock.elapsed();
}

void Clock::setElapsed()
{
    _elapsed = _elapsed_times.system + _elapsed_times.user;
}

boost::timer::cpu_timer &Clock::getClock()
{
    return _clock;
}

boost::timer::nanosecond_type Clock::getSecond() const
{
    return _second;
}

boost::timer::cpu_times Clock::getElapsedTime() const
{
    return _elapsed_times;
}

boost::timer::nanosecond_type Clock::getElapsed() const
{
    return _elapsed;
}
