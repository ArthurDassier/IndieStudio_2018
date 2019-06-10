/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** tests_character.cpp
*/

#include <vector>
#include <string>
#include "gtest/gtest.h"
#include "Game/Generation.hpp"

TEST(TestGeneration, TestGeneration)
{
    std::vector<std::string> map;

    map.push_back("1111111111");
    map.push_back("0000000000");
    map.push_back("0000000000");
    map.push_back("0000000000");
    ASSERT_EQ(getResult(map), "1111111111\n0000000000\n0000000000\n0000000000\n");
    ASSERT_EQ(isBlockNext(map, 2, 5), true);
    ASSERT_EQ(isBlockNext(map, 1, 5), false);
}
