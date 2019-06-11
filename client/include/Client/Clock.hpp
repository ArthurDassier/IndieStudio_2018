/*
** EPITECH PROJECT, 2019
** clock
** File description:
** clock
*/

#pragma once

#include "boost/timer/timer.hpp"

namespace client
{
    class Clock
    {
        public:
            Clock();
            ~Clock() = default;
            void setElapsedTime();
            void setElapsed();
            boost::timer::cpu_timer &getClock();
            boost::timer::nanosecond_type getSecond() const;
            boost::timer::cpu_times getElapsedTime() const;
            boost::timer::nanosecond_type getElapsed() const;

        private:
            boost::timer::cpu_timer _clock;
            boost::timer::nanosecond_type _second;
            boost::timer::cpu_times _elapsed_times;
            boost::timer::nanosecond_type _elapsed;
    };
}; // namespace client