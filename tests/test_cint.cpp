#include <gtest/gtest.h>
#include "uint.h"
#include "error.h"

using namespace large_numbers;

TEST(UInt, Constructions) {
    UInt zero;
    UInt one("1", 16);
    UInt one2(1);
    EXPECT_EQ(one, one2);

    UInt two = one * 2;
    UInt two2("2", 16);
    EXPECT_EQ(two, two2);
}

TEST(UInt, Comparison) {
    UInt zero;
    EXPECT_EQ(zero, 0);
    EXPECT_NE(zero, 1);
    UInt one("1", 16);
    UInt one2(1);
    UInt two(2);
    EXPECT_EQ(one, one2);
    EXPECT_NE(one, two);
}

TEST(UInt, Addition) {
    UInt a(1);
    UInt b(2);
    a += b;
    EXPECT_EQ(UInt(3), a);
    a = 1;
    b = 2;
    UInt c = a + b;
    EXPECT_EQ(UInt(3), c);
    EXPECT_EQ(UInt(5), c + 2);

    UInt x("12341234123412341234123412341234", 16);
    x += x;
    EXPECT_EQ(UInt("24682468246824682468246824682468", 16), x);

    UInt y("0x88888888888888888888888888888888", 16);
    UInt z = y;
    z += y;
    EXPECT_EQ(UInt("0x111111111111111111111111111111110", 16), z);
    y = 0;
    z = z + y;
    EXPECT_EQ(UInt("0x111111111111111111111111111111110", 16), z);

    x = UInt("0x88888888888888888888888888888888", 16);
    y = UInt("0xFFF888888888888888888888", 16);
    EXPECT_EQ(x + y, UInt("0x88888889888111111111111111111110", 16));
}

TEST(UInt, Substraction) {
    UInt a(5);
    UInt b(2);
    a -= b;
    EXPECT_EQ(UInt(3), a);
    a = 5;
    b = 2;
    UInt c = a - b;
    EXPECT_EQ(UInt(3), c);

    UInt k("24682468246824682468246824682468", 16);
    UInt x("12341234123412341234123412341234", 16);
    k -= x;
    EXPECT_EQ(UInt("12341234123412341234123412341234", 16), k);

    UInt z("88888888888888888888888888888888", 16);
    UInt y(           "777777777777777777777", 16);
    z = z - y;
    EXPECT_EQ(UInt("88888888888111111111111111111111", 16), z);
    z = 0;
    EXPECT_EQ(y, y-z);

    z = UInt("0x100000000000000000000000000000000", 16);
    y = UInt(0x1);
    EXPECT_EQ(UInt("0xffffffffffffffffffffffffffffffff", 16), z - y);

    z = UInt("0x100000000000000000000000000000000", 16);
    y = UInt("0xffffffffffffffffffffffffffffffff", 16);
    EXPECT_EQ(UInt(0x1), z-y);
}

TEST(UInt, MultiplyImmidiate) {
    UInt a(1234);
    UInt b = a * 5678;
    EXPECT_EQ(UInt(1234 * 5678), b);

    UInt x("FFFFFFFF", 16);
    EXPECT_EQ(UInt(0xFFFFFFFFULL), x);
    UInt y = x * 16;
    EXPECT_EQ(UInt("FFFFFFFF0", 16), y);
}

TEST(UInt, Base10String) {
    UInt test("256");
    EXPECT_EQ("0X100", test.toString(16));

    UInt a("10000000000");
    EXPECT_EQ("0X2540BE400", a.toString(16));

    UInt rsa_100_a("37975227936943673922808872755445627854565536638199");
    UInt rsa_100_b("40094690950920881030683735292761468389214899724061");
    EXPECT_EQ("0X19FBD41D69AA3D86009A967DB3379C63CD501F24F7", rsa_100_a.toString(16));
    EXPECT_EQ("0X1B6F141F98EEB619BC0360220160A5F75EA07CDF1D", rsa_100_b.toString(16));
}

TEST(UInt, Base16String) {
    UInt test("ABCDABCD", 16);
    EXPECT_EQ("0XABCDABCD", test.toString(16));
}

TEST(UInt, ErrorConditions) {
    EXPECT_THROW(new large_numbers::UInt("TEST", 3), large_numbers::Error);
    EXPECT_THROW(large_numbers::UInt().toString(3), large_numbers::Error);
}