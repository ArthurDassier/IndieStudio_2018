/*
** EPITECH PROJECT, 2019
** clock
** File description:
** clock
*/

#include "Client/Clock.hpp"

client::Clock::Clock():
    _clock(),
    _second(50000000LL)
{
}

void client::Clock::setElapsedTime()
{
    _elapsed_times = _clock.elapsed();
}

void client::Clock::setElapsed()
{
    _elapsed = _elapsed_times.system + _elapsed_times.user;
}

boost::timer::cpu_timer &client::Clock::getClock()
{
    return _clock;
}

boost::timer::nanosecond_type client::Clock::getSecond() const
{
    return _second;
}

boost::timer::cpu_times client::Clock::getElapsedTime() const
{
    return _elapsed_times;
}

boost::timer::nanosecond_type client::Clock::getElapsed() const
{
    return _elapsed;
}
