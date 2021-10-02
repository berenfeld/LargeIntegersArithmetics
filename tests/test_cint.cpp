#include <gtest/gtest.h>
#include "uint.h"

TEST(UInt, Constructions)
{
    large_numbers::UInt zero;
    large_numbers::UInt one("1", 16);
    large_numbers::UInt one2(1);
    EXPECT_EQ(one, one2);

    large_numbers::UInt two = one * 2;
    large_numbers::UInt two2("2", 16);
    EXPECT_EQ(two, two2);
}

TEST(UInt, Base16String)
{
    large_numbers::UInt test("ABCDABCD", 16);
    EXPECT_EQ("ABCDABCD", test.toString(16));
}