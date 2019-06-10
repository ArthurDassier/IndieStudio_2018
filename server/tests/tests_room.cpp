/*
** EPITECH PROJECT, 2019
** tests_room.cpp
** File description:
** tests_room
*/

#include "gtest/gtest.h"
#include "../include/server/server.hpp"

TEST(TestRoom, TestNbParticipants)
{
    server::Room room;

    ASSERT_EQ(room.nbParticipants(), 0);
}