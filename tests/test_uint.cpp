#include "error.h"
#include "uint.h"
#include "utils.h"
#include <gtest/gtest.h>

using namespace large_numbers;

TEST(UInt, Constructions)
{
    UInt zero;
    UInt one("1");
    UInt one2(1);
    EXPECT_EQ(one, one2);

    UInt two = one * 2;
    UInt two2("2");
    EXPECT_EQ(two, two2);
}

TEST(UInt, Comparison)
{
    UInt zero;
    EXPECT_EQ(zero, 0);
    EXPECT_NE(zero, 1);
    UInt one("1");
    UInt one2(1);
    UInt two(2);
    EXPECT_EQ(one, one2);
    EXPECT_NE(one, two);
    EXPECT_TRUE(one >= one2);
    EXPECT_TRUE(one <= one2);
    EXPECT_TRUE(one < two);
    EXPECT_TRUE(two > one);
    EXPECT_FALSE(one >= two);
    EXPECT_FALSE(two <= one);

    UInt four(4);
    UInt six(6);
    EXPECT_FALSE(four > six);
    EXPECT_FALSE(four >= six);
    EXPECT_TRUE(four < six);
    EXPECT_TRUE(four <= six);
}

TEST(UInt, Addition)
{
    UInt a(1);
    UInt b(2);
    a += b;
    EXPECT_EQ(UInt(3), a);
    a = 1;
    b = 2;
    UInt c = a + b;
    EXPECT_EQ(UInt(3), c);
    EXPECT_EQ(UInt(5), c + 2);

    UInt x("12341234123412341234123412341234");
    x += x;
    EXPECT_EQ(UInt("24682468246824682468246824682468"), x);

    UInt y("0x88888888888888888888888888888888");
    UInt z = y;
    z += y;
    EXPECT_EQ(UInt("0x111111111111111111111111111111110"), z);
    y = 0;
    z = z + y;
    EXPECT_EQ(UInt("0x111111111111111111111111111111110"), z);

    x = UInt("0x88888888888888888888888888888888");
    y = UInt("0xFFF888888888888888888888");
    EXPECT_EQ(x + y, UInt("0x88888889888111111111111111111110"));

    for (auto i = 0; i < 10; ++i) {
        UInt r1 = large_numbers::rand();
        UInt r2 = large_numbers::rand();
        UInt r1_r2 = r1 + r2;
        EXPECT_EQ(r1_r2, r1 + r2);
        UInt r1b = r1_r2 - r2;
        UInt r2b = r1_r2 - r1;
        EXPECT_EQ(r1b, r1);
        EXPECT_EQ(r2b, r2);
    }

    int return_code;
    for (auto i = 0; i < 10; ++i) {
        UInt r1 = large_numbers::rand();
        UInt r2 = large_numbers::rand();
        std::string command = "python -c 'print(hex(" + r1.toString(16) + " + " + r2.toString(16) + "))'";
        std::string result = executeCommand(command, return_code);
        EXPECT_EQ(0, return_code) << "Failed executing command " << command;
        UInt r1_r2(result);
        EXPECT_EQ(r1_r2, r1 + r2);
    }
}

TEST(UInt, Substraction)
{
    UInt a(5);
    UInt b(2);
    a -= b;
    EXPECT_EQ(UInt(3), a);
    a = 5;
    b = 2;
    UInt c = a - b;
    EXPECT_EQ(UInt(3), c);

    UInt k("24682468246824682468246824682468");
    UInt x("12341234123412341234123412341234");
    k -= x;
    EXPECT_EQ(UInt("12341234123412341234123412341234"), k);

    UInt z("88888888888888888888888888888888");
    UInt y("777777777777777777777");
    z = z - y;
    EXPECT_EQ(UInt("88888888888111111111111111111111"), z);
    z = 0;
    EXPECT_EQ(y, y - z);

    z = UInt("0x100000000000000000000000000000000");
    y = UInt(0x1);
    EXPECT_EQ(UInt("0xffffffffffffffffffffffffffffffff"), z - y);

    z = UInt("0x100000000000000000000000000000000");
    y = UInt("0xffffffffffffffffffffffffffffffff");
    EXPECT_EQ(UInt(0x1), z - y);

    int return_code;
    for (auto i = 0; i < 10; ++i) {
        UInt r1 = large_numbers::rand();
        UInt r2 = large_numbers::rand();
        UInt r1_r2 = r1 + r2;
        std::string command = "python -c 'print(hex(" + r1_r2.toString(16) + " - " + r1.toString(16) + "))'";
        std::string result = executeCommand(command, return_code);
        EXPECT_EQ(0, return_code);
        UInt r2b(result);
        EXPECT_EQ(r2b, r2);
    }
}

TEST(UInt, MultiplyImmidiate)
{
    UInt a(1234);
    UInt b = a * 5678;
    EXPECT_EQ(UInt(1234 * 5678), b);

    UInt x("FFFFFFFF");
    EXPECT_EQ(UInt(0xFFFFFFFFULL), x);
    UInt y = x * 16;
    EXPECT_EQ(UInt("FFFFFFFF0"), y);
}

TEST(UInt, Shift)
{
    UInt test("0x10000000");
    EXPECT_EQ(UInt("0x10000000"), test << 0);
    EXPECT_EQ(UInt("0x20000000"), test << 1);
    EXPECT_EQ(UInt("0x100000000"), test << 4);
    EXPECT_EQ(UInt("0x100000000000"), test << 16);
    EXPECT_EQ(UInt("0x1000000000000000"), test << 32);

    UInt test2("0x1234567812345678");
    EXPECT_EQ(UInt("0x12345678123456780"), test2 << 4);
    EXPECT_EQ(UInt("0X2468ACF02468ACF00"), test2 << 5);
    EXPECT_EQ(UInt("0x123456781234567800"), test2 << 8);
    EXPECT_EQ(UInt("0x123456781234567800000000"), test2 << 32);
    EXPECT_EQ(UInt("0X2468ACF02468ACF0000000000"), test2 << 37);
    EXPECT_EQ(UInt("0x12345678123456780000000000000000"), test2 << 64);
    EXPECT_EQ(UInt("0x123456781234567800000000000000000000000000000000"), test2 << 128);
}

TEST(UInt, Base10String)
{
    UInt zero("");
    EXPECT_TRUE(zero == 0);
    EXPECT_EQ("0", zero.toString());

    UInt test("256");
    EXPECT_EQ("256", test.toString());
    EXPECT_EQ("0X100", test.toString(16));

    UInt a("10000000000");
    EXPECT_EQ("0X2540BE400", a.toString(16));

    UInt rsa_100_a("37975227936943673922808872755445627854565536638199");
    UInt rsa_100_b("40094690950920881030683735292761468389214899724061");
    EXPECT_EQ("37975227936943673922808872755445627854565536638199", rsa_100_a.toString());
    EXPECT_EQ("40094690950920881030683735292761468389214899724061", rsa_100_b.toString());
    EXPECT_EQ("0X19FBD41D69AA3D86009A967DB3379C63CD501F24F7", rsa_100_a.toString(16));
    EXPECT_EQ("0X1B6F141F98EEB619BC0360220160A5F75EA07CDF1D", rsa_100_b.toString(16));
}

TEST(UInt, Base16String)
{
    UInt test("ABCDABCD");
    EXPECT_EQ("0XABCDABCD", test.toString(16));
}

TEST(UInt, ErrorConditions)
{
    EXPECT_THROW(new UInt("TEST", 3), large_numbers::Error);
    EXPECT_THROW(UInt().toString(3), large_numbers::Error);
    EXPECT_THROW(UInt("-3"), large_numbers::Error);
    EXPECT_THROW(UInt("prime"), large_numbers::Error);
    int unused;
}

TEST(UInt, Division)
{
    UInt a(7);
    UInt b(2);
    a /= b;
    EXPECT_EQ(UInt(3), a);
    EXPECT_EQ(UInt(1), a % b);

    a = 7;
    b = 2;
    UInt c = a / b;
    EXPECT_EQ(UInt(3), c);

    a = 256;
    b = 10;
    UInt d;
    UInt::div_mod(a, b, c, d);
    EXPECT_EQ(UInt(25), c);
    EXPECT_EQ(UInt(6), d);

    UInt k("24682468246824682468246824682468", 16);
    UInt x("12341234123412341234123412341234", 16);
    c = k / x;
    EXPECT_EQ(UInt(2), c);

    c = k / 2;
    EXPECT_EQ(x, c);

    EXPECT_EQ(a, a / 1);
    EXPECT_EQ(b, b / 1);
    EXPECT_EQ(c, c / 1);
    EXPECT_EQ(k, k / 1);
}

TEST(UInt, Random)
{
    // test that we have fixed seed for now
    srand(0);
    EXPECT_EQ(UInt("0X327B23C6"), large_numbers::rand(1));
    EXPECT_EQ(UInt("0X66334873"), large_numbers::rand(2));
    EXPECT_EQ(UInt("0X19495CFF2AE8944A"), large_numbers::rand(3));
    EXPECT_EQ(
        UInt("0X238E1F2946E87CCD3D1B58BA507ED7AB2EB141F241B71EFB79E2A9E37545E146515F007C5BD062C2122008544DB127F8"),
        large_numbers::rand());
}