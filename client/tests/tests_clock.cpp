/*
** EPITECH PROJECT, 2019
** tests_clock.cpp
** File description:
** tests_clock
*/

#include "gtest/gtest.h"
#include "Client/Graphic.hpp"

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
