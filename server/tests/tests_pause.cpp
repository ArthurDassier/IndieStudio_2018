/*
** EPITECH PROJECT, 2019
** tests_pause.cpp
** File description:
** tests_pause
*/

#include "gtest/gtest.h"
#include "../include/server/server.hpp"

TEST(TestClock, TestGetElapsedTime)
{
    Server server;

    ASSERT_FALSE(server.getPause());
}