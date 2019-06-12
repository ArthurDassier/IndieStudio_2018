/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** tests_audio.cpp
*/

#include "gtest/gtest.h"
#include "SFX/Audio.hpp"

TEST(TestAudio, TestGetName)
{
    sfx::Audio audio("test");

    ASSERT_EQ(audio.getName(), "test");
}