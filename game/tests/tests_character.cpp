/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** tests_character.cpp
*/

#include "gtest/gtest.h"
#include "../include/Character.hpp"

TEST(TestCharacter, TestClass)
{
    game::Character test;

    test.setDirection("right");
    test.setId(7);
    test.setPosition3df(irr::core::vector3df({2, 22, 222}));
    test.setPosition({1, 11, 111});
    test.setSkin(3);

    ASSERT_EQ(test.getDirection(), "right");
    ASSERT_EQ(test.getId(), 7);
    ASSERT_EQ(test.getPosition3df(), irr::core::vector3df({2, 22, 222}));
    ASSERT_EQ(test.getPosition().x, 1);
    ASSERT_EQ(test.getPosition().y, 11);
    ASSERT_EQ(test.getPosition().z, 111);
    ASSERT_EQ(test.getSkin(), 3);
}