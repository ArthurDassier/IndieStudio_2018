/*
** EPITECH PROJECT, 2019
** tests_server.cpp
** File description:
** tests_server
*/

#include "gtest/gtest.h"
#include "../include/server/server.hpp"

TEST(TestClock, TestGetElapsedTime)
{
    server::Server server;

    ASSERT_FALSE(server.getPause());
}