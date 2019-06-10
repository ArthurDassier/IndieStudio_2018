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
    client::EngineGraphic graph;

    ASSERT_EQ(graph.getData(), "");
}

TEST(TestIrrlicht, getData)
{
    client::EngineGraphic graph;

    graph.dataMove("up");
    ASSERT_NE(graph.getData(), "");
}

TEST(TestIrrlicht, clearData)
{
    client::EngineGraphic graph;

    graph.dataMove("up");
    graph.clearData();
    ASSERT_EQ(graph.getData(), "");
}