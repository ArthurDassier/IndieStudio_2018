/*
** EPITECH PROJECT, 2019
** tests_server.cpp
** File description:
** tests_server
*/

#include "gtest/gtest.h"
#include "Server/Server.hpp"

TEST(TestClock, TestGetElapsedTime)
{
    Server server;

    ASSERT_FALSE(server.getPause());
}
