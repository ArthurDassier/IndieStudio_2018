/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** tests_audio.cpp
*/

#include "gtest/gtest.h"
#include "SFX/Audio.hpp"

TEST(TestMusic, TestGetName)
{
    sfx::Music music("test", "./path/to/file/test.mp3");

    ASSERT_EQ(music.getName(), "test");
}