#include <gtest/gtest.h>
#include "uint.h"

TEST(UInt, Constructions)
{
    large_numbers::UInt zero;
    large_numbers::UInt one("1", 16);
    large_numbers::UInt two = one * 2;
    large_numbers::UInt another_two("2", 16);
    EXPECT_EQ(two, another_two);
}

TEST(UInt, Base16String)
{
    large_numbers::UInt test("ABCDABCD", 16);
    EXPECT_EQ("ABCDABCD", test.toString(16));
}