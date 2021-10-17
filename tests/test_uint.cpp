#include "error.h"
#include "primes_base.h"
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
    EXPECT_EQ(UInt(3), a - 2);
    a -= 2;
    EXPECT_EQ(UInt(3), a);

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
    a *= 5678;
    EXPECT_EQ(UInt(1234 * 5678), a);
    UInt c = a / 5678;
    EXPECT_EQ(UInt(1234), c);
    a /= 5678;
    EXPECT_EQ(UInt(1234), a);

    UInt x("FFFFFFFF");
    EXPECT_EQ(UInt(0xFFFFFFFFULL), x);
    UInt y = x * 16;
    EXPECT_EQ(UInt("FFFFFFFF0"), y);
}

TEST(UInt, Multiply)
{
    UInt a(1234);
    UInt b(5678);
    EXPECT_EQ(UInt(1234 * 5678), a * b);
    a *= b;
    EXPECT_EQ(UInt(1234 * 5678), a);

    UInt x("FFFFFFFF");
    EXPECT_EQ(UInt(0xFFFFFFFFULL), x);
    UInt y = x * UInt(16);
    EXPECT_EQ(UInt("FFFFFFFF0"), y);

    for (auto i = 0; i < 10; ++i) {
        UInt r1 = large_numbers::rand();
        UInt r2 = large_numbers::rand();
        UInt r1_r2 = r1 * r2;
        EXPECT_EQ(r1_r2, r1 * r2);
        UInt r1b = r1_r2 / r2;
        UInt r2b = r1_r2 / r1;
        EXPECT_EQ(r1b, r1);
        EXPECT_EQ(r2b, r2);
    }

    int return_code;
    for (auto i = 0; i < 10; ++i) {
        UInt r1 = large_numbers::rand();
        UInt r2 = large_numbers::rand();
        std::string command = "python -c 'print(" + r1.toString() + " * " + r2.toString() + ")'";
        std::string result = executeCommand(command, return_code);
        EXPECT_EQ(0, return_code) << "Failed executing command " << command;
        UInt r1_r2(result);
        EXPECT_EQ(r1_r2, r1 * r2);
    }
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
    UInt zero;
    EXPECT_EQ("0X0", zero.toString(16));
    UInt test("ABCDABCD");
    EXPECT_EQ("0XABCDABCD", test.toString(16));
}

TEST(UInt, ErrorConditions)
{
    EXPECT_THROW(new UInt("TEST", 3), large_numbers::Error);
    EXPECT_THROW(UInt().toString(3), large_numbers::Error);
    EXPECT_THROW(UInt("-3"), large_numbers::Error);
    EXPECT_THROW(UInt("prime"), large_numbers::Error);
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

    int return_code;
    for (auto i = 0; i < 10; ++i) {
        UInt r1 = large_numbers::rand();
        UInt r2 = large_numbers::rand();
        UInt r1_r2 = r1 * r2;
        std::string command = "python -c 'print(" + r1_r2.toString() + " // " + r2.toString() + ")'";
        std::string result = executeCommand(command, return_code);
        EXPECT_EQ(0, return_code) << "Failed executing command " << command;
        UInt r1b(result);
        EXPECT_EQ(r1b, r1);
    }
}

TEST(UInt, Modulo)
{
    UInt a = 256;
    UInt b = 10;
    UInt c, d;
    UInt::div_mod(a, b, c, d);
    EXPECT_EQ(UInt(25), c);
    EXPECT_EQ(UInt(6), d);

    UInt base = 2;
    uint32_t exp = 10;
    UInt modulo = 1000;
    EXPECT_EQ(UInt::power_modulo(base, exp, modulo), 24);
    base.raiseToPower(10, 1000);
    EXPECT_EQ(base, 24);
}

TEST(UInt, power)
{
    UInt one = 1;
    EXPECT_EQ(UInt::pow(one, 1), 1);
    EXPECT_EQ(UInt::pow(one, 2), 1);
    EXPECT_EQ(UInt::pow(one, 0xFFFF), 1);
    one.raiseToPower(1);
    EXPECT_EQ(one, 1);
    one.raiseToPower(2);
    EXPECT_EQ(one, 1);
    one.raiseToPower(0xFFFF);
    EXPECT_EQ(one, 1);

    UInt two = 2;
    EXPECT_EQ(UInt::pow(two, 1), 2);
    EXPECT_EQ(UInt::pow(two, 2), 4);
    EXPECT_EQ(UInt::pow(two, 31), 0x80000000);
    two.raiseToPower(1);
    EXPECT_EQ(two, 2);
    two.raiseToPower(2);
    EXPECT_EQ(two, 4);
    two.raiseToPower(4);
    EXPECT_EQ(two, 0x100);

    int return_code;
    for (auto i = 0; i < 10; ++i) {
        // cant go too large, otherwise it will take too long
        UInt base = large_numbers::rand(4);
        uint32_t exp = ::rand() % 10;
        std::string command = "python -c 'print(" + base.toString() + " ** " + std::to_string(exp) + ")'";
        std::string result = executeCommand(command, return_code);
        EXPECT_EQ(0, return_code) << "Failed executing command " << command;
        UInt base_to_exp(result);
        EXPECT_EQ(base_to_exp, UInt::pow(base, exp));
    }
}

TEST(UInt, Random)
{
    // test that we have fixed seed for now
    srand(0);
    EXPECT_EQ(UInt("0X327B23C6"), large_numbers::rand(1));
    EXPECT_EQ(UInt("0X66334873"), large_numbers::rand(2));
    EXPECT_EQ(UInt("0X19495CFF000000002AE8944A"), large_numbers::rand(3));
    EXPECT_EQ(UInt("0X238E1F290000000046E87CCD000000003D1B58BA00000000507ED7AB"), large_numbers::rand());
}

TEST(UInt, sqrt)
{
    UInt x = 1;
    EXPECT_EQ(x.sqrt(), UInt(1));
    x = 4;
    UInt result(0);
    x.sqrt(result);
    EXPECT_EQ(result, UInt(2));
    EXPECT_EQ(x.sqrt(), UInt(2));
    x = 25;
    EXPECT_EQ(x.sqrt(), UInt(5));
    x = UInt("4000000", 10);
    EXPECT_EQ(x.sqrt(), UInt("2000", 10));
    x = UInt("4000000000000000000000000000000000000000000000000", 10);
    EXPECT_EQ(x.sqrt(), UInt("2000000000000000000000000", 10));

    for (auto i = 0; i < 10; ++i) {
        UInt base = large_numbers::rand(4);
        UInt powered = UInt::pow(base, 2);
        UInt result(0);
        powered.sqrt(result);
        EXPECT_EQ(base, result);
    }
}

TEST(UInt, BasicPrimeCheck)
{
    EXPECT_TRUE(isPrime(0));
    EXPECT_TRUE(isPrime(1));
    EXPECT_TRUE(isPrime(2));
    EXPECT_TRUE(isPrime(3));
    EXPECT_TRUE(isPrime(5));
    EXPECT_TRUE(isPrime(7));
    EXPECT_TRUE(isPrime(101));
    EXPECT_TRUE(isPrime(997));

    EXPECT_FALSE(isPrime(4));
    EXPECT_FALSE(isPrime(6));
    EXPECT_FALSE(isPrime(8));
    EXPECT_FALSE(isPrime(9));
    EXPECT_FALSE(isPrime(10));
    EXPECT_FALSE(isPrime(1001));
}

TEST(UInt, PrimesBase)
{
    PrimesBase base(5); // 2,3,5,7,11
    EXPECT_TRUE(base.contains(2));
    EXPECT_TRUE(base.contains(3));
    EXPECT_TRUE(base.contains(5));
    EXPECT_TRUE(base.contains(10));
    EXPECT_TRUE(base.contains(4));
    EXPECT_TRUE(base.contains(40));
    EXPECT_TRUE(base.contains(2 * 3 * 5 * 7 * 9 * 2 * 3 * 5 * 7 * 9));

    EXPECT_FALSE(base.contains(13));
    EXPECT_FALSE(base.contains(29));
    EXPECT_FALSE(base.contains(2 * 3 * 5 * 7 * 17));
}

TEST(UInt, gcd)
{
    EXPECT_EQ(UInt::gcd(2, 2), 2);
    EXPECT_EQ(UInt::gcd(2, 3), 1);
    EXPECT_EQ(UInt::gcd(3, 2), 1);
    EXPECT_EQ(UInt::gcd(4, 2), 2);
    EXPECT_EQ(UInt::gcd(2, 4), 2);
    EXPECT_EQ(UInt::gcd(20, 36), 4);
    EXPECT_EQ(UInt::gcd(36, 48), 12);

    UInt a = 36;
    EXPECT_EQ(a.gcdWith(48), 12);
}

TEST(UInt, StartWithRsa100)
{
    UInt rsa_100(
        "1522605027922533360535618378132637429718068114961380688657908494580122963258952897654000350692006139");
    UInt a = rsa_100.sqrt() += 1;
    PrimesBase base(512);
    for (int i = 0; i < 10; ++i) {
        UInt candidate = UInt::power_modulo(a, 2, rsa_100);
        std::cout << "checking " << candidate << std::endl;
        if (base.contains(candidate)) {
            std::cout << "Found B-smooth ! : " << candidate << std::endl;
        }
        a += 1;
    }
}

TEST(UInt, StartWithRsa100Optimized)
{
    UInt rsa_100(
        "1522605027922533360535618378132637429718068114961380688657908494580122963258952897654000350692006139");
    UInt a = rsa_100.sqrt() += 1;
    UInt a_2 = (a * 2) % rsa_100;
    UInt a_square = a.raiseToPower(2, rsa_100);
    PrimesBase base(512);
    int i = 0;
    do {
        std::cout << "checking " << a << std::endl;
        if (base.contains(a)) {
            std::cout << "Found B-smooth ! : " << a << std::endl;
        }
        a += a_2;
        a += ((2 * (i+1)) - 1);
        ++i;
    } while (i < 10);
}