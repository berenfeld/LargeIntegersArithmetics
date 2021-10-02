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

TEST(UInt, MultiplyImmidiate)
{
    large_numbers::UInt a(1234);
    large_numbers::UInt b = a * 5678;
    EXPECT_EQ(large_numbers::UInt(1234 * 5678), b);

    large_numbers::UInt x("FFFFFFFF", 16);
    EXPECT_EQ(large_numbers::UInt(0xFFFFFFFFULL), x);
    large_numbers::UInt y = x * 16;
    EXPECT_EQ(large_numbers::UInt("FFFFFFFF0", 16), y);
}


TEST(UInt, Base16String)
{
    large_numbers::UInt test("ABCDABCD", 16);
    EXPECT_EQ("ABCDABCD", test.toString(16));
}