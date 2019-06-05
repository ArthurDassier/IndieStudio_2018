/*
** EPITECH PROJECT, 2019
** tests_clock.cpp
** File description:
** tests_clock
*/

#include "gtest/gtest.h"
#include "../include/client/Irrlicht.hpp"

TEST(TestIrrlicht, getDataNULL)
{
    EngineGraphic graph;

    ASSERT_EQ(graph.getData(), "");
}

TEST(TestIrrlicht, getData)
{
    EngineGraphic graph;

    graph.dataMove("up");
    ASSERT_NE(graph.getData(), "");
}

TEST(TestIrrlicht, clearData)
{
    EngineGraphic graph;

    graph.dataMove("up");
    graph.clearData();
    ASSERT_EQ(graph.getData(), "");
}

// TEST(TestClock, getSecond)
// {
//     Clock clock;
//     boost::timer::nanosecond_type second(70000000LL);

//     ASSERT_EQ(clock.getSecond(), second);
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