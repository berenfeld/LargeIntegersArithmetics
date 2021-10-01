#include <gtest/gtest.h>
#include "uint.h"

TEST(UInt, Base16String)
{
    large_numbers::UInt test("ABCDABCD", 16);
    EXPECT_EQ("ABCDABCD", test.toString(16));
}