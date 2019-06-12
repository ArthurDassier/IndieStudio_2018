/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** tests_audio.cpp
*/

#include "gtest/gtest.h"
#include "Error/Error.hpp"

TEST(TestError, TestErrorWhatWithoutComponent)
{
    EXPECT_THROW({
        try {
            throw(error::Error("test"));
        } catch(const error::Error& e) {
            EXPECT_STREQ("\033[1;31mUnknown: test\033[0m", e.what());
            throw;
        }
    }, error::Error);
}

TEST(TestError, TestErrorWhat)
{
    EXPECT_THROW({
        try {
            throw(error::Error("test", "Component"));
        } catch(const error::Error& e) {
            EXPECT_STREQ("\033[1;31mComponent: test\033[0m", e.what());
            throw;
        }
    }, error::Error);
}

TEST(TestError, TestClientWhat)
{
    EXPECT_THROW({
        try {
            throw(error::ClientError("test"));
        } catch(const error::Error& e) {
            EXPECT_STREQ("\033[1;31mClient: test\033[0m", e.what());
            throw;
        }
    }, error::Error);
}

TEST(TestError, TestGameWhat)
{
    EXPECT_THROW({
        try {
            throw(error::GameError("test"));
        } catch(const error::Error& e) {
            EXPECT_STREQ("\033[1;31mGame: test\033[0m", e.what());
            throw;
        }
    }, error::Error);
}

TEST(TestError, TestServerWhat)
{
    EXPECT_THROW({
        try {
            throw(error::ServerError("test"));
        } catch(const error::Error& e) {
            EXPECT_STREQ("\033[1;31mServer: test\033[0m", e.what());
            throw;
        }
    }, error::Error);
}

TEST(TestError, TestSFXWhat)
{
    EXPECT_THROW({
        try {
            throw(error::SFXError("test"));
        } catch(const error::Error& e) {
            EXPECT_STREQ("\033[1;31mSFX: test\033[0m", e.what());
            throw;
        }
    }, error::Error);
}

TEST(TestError, TestUtilsWhat)
{
    EXPECT_THROW({
        try {
            throw(error::UtilsError("test"));
        } catch(const error::Error& e) {
            EXPECT_STREQ("\033[1;31mUtils: test\033[0m", e.what());
            throw;
        }
    }, error::Error);
}