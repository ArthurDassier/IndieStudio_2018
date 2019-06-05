#include "gtest/gtest.h"
#include "module_tmp/toto.hpp"

TEST(test_case_inutile, test_inutile)
{
    EXPECT_TRUE(0 + return_one() == 1);
}
