/*
** EPITECH PROJECT, 2019
** tests_room.cpp
** File description:
** tests_room
*/

#include "gtest/gtest.h"
#include "server/Server.hpp"

TEST(TestRoom, TestNbParticipants)
{
    Room room;

    ASSERT_EQ(room.nbParticipants(), 0);
}
