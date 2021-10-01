#include <gtest/gtest.h>
#include "uint.h"

TEST(UInt, Base16String)
{
    large_numbers::UInt test("ABCDEFGH", 16);
    EXPECT_EQ("ABCDEFGH", test.toString(16));
}