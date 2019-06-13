/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** tests_audio.cpp
*/

#include "gtest/gtest.h"
#include "SFX/Audio.hpp"

TEST(TestSound, TestGetName)
{
    sfx::Sound sound("test", "./path/to/file/test.mp3");

    ASSERT_EQ(sound.getName(), "test");
}