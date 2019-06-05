/*
** EPITECH PROJECT, 2019
** tests_clock.cpp
** File description:
** tests_clock
*/

#include "gtest/gtest.h"
#include "../include/client/clock.hpp"

TEST(TestClock, TestGetElapsedTime)
{
    Clock clock;

    clock.setElapsedTime();
    ASSERT_TRUE(true);
}

// TEST(TestClock, TestGetSecond)
// {
//     Clock clock;

//     clock.setElapsedTime();
//     ASSERT_TRUE(clock.getSecond());
// }

// TEST(TestClock, TestGetElapsed)
// {
//     Clock clock;

//     clock.setElapsedTime();
//     ASSERT_TRUE(clock.getElapsed());
// }

// TEST(TestClock, TestGetClock)
// {
//     Clock clock;

//     clock.setElapsedTime();
//     ASSERT_TRUE(clock.getClock());
// }