#include "cerror.h"
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
    ASSERT_EQ(one, one2);

    UInt two = one * 2;
    UInt two2("2");
    ASSERT_EQ(two, two2);
}

TEST(UInt, Comparison)
{
    UInt zero;
    ASSERT_EQ(zero, 0);
    ASSERT_NE(zero, 1);
    UInt one("1");
    UInt one2(1);
    UInt two(2);
    ASSERT_EQ(one, one2);
    ASSERT_NE(one, two);
    ASSERT_TRUE(one >= one2);
    ASSERT_TRUE(one <= one2);
    ASSERT_TRUE(one < two);
    ASSERT_TRUE(two > one);
    ASSERT_FALSE(one >= two);
    ASSERT_FALSE(two <= one);

    UInt four(4);
    UInt six(6);
    ASSERT_FALSE(four > six);
    ASSERT_FALSE(four >= six);
    ASSERT_TRUE(four < six);
    ASSERT_TRUE(four <= six);
}

TEST(UInt, Addition)
{
    UInt a(1);
    UInt b(2);
    a += b;
    ASSERT_EQ(UInt(3), a);
    a = 1;
    b = 2;
    UInt c = a + b;
    ASSERT_EQ(UInt(3), c);
    ASSERT_EQ(UInt(5), c + 2);

    UInt x("12341234123412341234123412341234");
    x += x;
    ASSERT_EQ(UInt("24682468246824682468246824682468"), x);

    UInt y("0x88888888888888888888888888888888");
    UInt z = y;
    z += y;
    ASSERT_EQ(UInt("0x111111111111111111111111111111110"), z);
    y = 0;
    z = z + y;
    ASSERT_EQ(UInt("0x111111111111111111111111111111110"), z);

    x = UInt("0x88888888888888888888888888888888");
    y = UInt("0xFFF888888888888888888888");
    ASSERT_EQ(x + y, UInt("0x88888889888111111111111111111110"));

    for (auto i = 0; i < 10; ++i) {
        UInt r1 = large_numbers::rand();
        UInt r2 = large_numbers::rand();
        UInt r1_r2 = r1 + r2;
        ASSERT_EQ(r1_r2, r1 + r2);
        UInt r1b = r1_r2 - r2;
        UInt r2b = r1_r2 - r1;
        ASSERT_EQ(r1b, r1);
        ASSERT_EQ(r2b, r2);
    }

    int return_code;
    for (auto i = 0; i < 10; ++i) {
        UInt r1 = large_numbers::rand();
        UInt r2 = large_numbers::rand();
        std::string command = "python -c 'print(hex(" + r1.toString(16) + " + " + r2.toString(16) + "))'";
        std::string result = executeCommand(command, return_code);
        ASSERT_EQ(0, return_code) << "Failed executing command " << command;
        UInt r1_r2(result);
        ASSERT_EQ(r1_r2, r1 + r2);
    }

    x = 123456;
    ++x;
    ASSERT_EQ(x, 123457);
    --x;
    ASSERT_EQ(x, 123456);
}

TEST(UInt, Substraction)
{
    UInt a(5);
    UInt b(2);
    a -= b;
    ASSERT_EQ(UInt(3), a);
    a = 5;
    b = 2;
    UInt c = a - b;
    ASSERT_EQ(UInt(3), c);
    ASSERT_EQ(UInt(3), a - 2);
    a -= 2;
    ASSERT_EQ(UInt(3), a);

    UInt k("24682468246824682468246824682468");
    UInt x("12341234123412341234123412341234");
    k -= x;
    ASSERT_EQ(UInt("12341234123412341234123412341234"), k);

    UInt z("88888888888888888888888888888888");
    UInt y("777777777777777777777");
    z = z - y;
    ASSERT_EQ(UInt("88888888888111111111111111111111"), z);
    z = 0;
    ASSERT_EQ(y, y - z);

    z = UInt("0x100000000000000000000000000000000");
    y = UInt(0x1);
    ASSERT_EQ(UInt("0xffffffffffffffffffffffffffffffff"), z - y);

    z = UInt("0x100000000000000000000000000000000");
    y = UInt("0xffffffffffffffffffffffffffffffff");
    ASSERT_EQ(UInt(0x1), z - y);

    int return_code;
    for (auto i = 0; i < 10; ++i) {
        UInt r1 = large_numbers::rand();
        UInt r2 = large_numbers::rand();
        UInt r1_r2 = r1 + r2;
        std::string command = "python -c 'print(hex(" + r1_r2.toString(16) + " - " + r1.toString(16) + "))'";
        std::string result = executeCommand(command, return_code);
        ASSERT_EQ(0, return_code);
        UInt r2b(result);
        ASSERT_EQ(r2b, r2);
    }
}

TEST(UInt, MultiplyImmidiate)
{
    UInt a(1234);
    UInt b = a * 5678;
    ASSERT_EQ(UInt(1234 * 5678), b);
    a *= 5678;
    ASSERT_EQ(UInt(1234 * 5678), a);
    UInt c = a / 5678;
    ASSERT_EQ(UInt(1234), c);
    a /= 5678;
    ASSERT_EQ(UInt(1234), a);

    UInt x("FFFFFFFF");
    ASSERT_EQ(UInt(0xFFFFFFFFULL), x);
    UInt y = x * 16;
    ASSERT_EQ(UInt("FFFFFFFF0"), y);
}

TEST(UInt, Multiply)
{
    UInt a(1234);
    UInt b(5678);
    ASSERT_EQ(UInt(1234 * 5678), a * b);
    a *= b;
    ASSERT_EQ(UInt(1234 * 5678), a);

    UInt x("FFFFFFFF");
    ASSERT_EQ(UInt(0xFFFFFFFFULL), x);
    UInt y = x * UInt(16);
    ASSERT_EQ(UInt("FFFFFFFF0"), y);

    x = UInt("5141529302805865183381910115");
    y = x * x;
    ASSERT_EQ(UInt("26435323571611366112288807319792539078573907425939313225"), y);
    UInt z = y * x;
    ASSERT_EQ(UInt("135917990772594441100379449743601350060335500746406797482563417569998782271780770875"), z);

    for (auto i = 0; i < 10; ++i) {
        UInt r1 = large_numbers::rand();
        UInt r2 = large_numbers::rand();
        UInt r1_r2 = r1 * r2;
        ASSERT_EQ(r1_r2, r1 * r2);
        UInt r1b = r1_r2 / r2;
        UInt r2b = r1_r2 / r1;
        ASSERT_EQ(r1b, r1);
        ASSERT_EQ(r2b, r2);
    }

    int return_code;
    for (auto i = 0; i < 10; ++i) {
        UInt r1 = large_numbers::rand();
        UInt r2 = large_numbers::rand();
        std::string command = "python -c 'print(" + r1.toString() + " * " + r2.toString() + ")'";
        std::string result = executeCommand(command, return_code);
        ASSERT_EQ(0, return_code) << "Failed executing command " << command;
        UInt r1_r2(result);
        ASSERT_EQ(r1_r2, r1 * r2);
    }
}

TEST(UInt, ShiftLeft)
{
    UInt test("0x10000000");
    ASSERT_EQ(UInt("0x10000000"), test << 0);
    ASSERT_EQ(UInt("0x20000000"), test << 1);
    ASSERT_EQ(UInt("0x100000000"), test << 4);
    ASSERT_EQ(UInt("0x100000000000"), test << 16);
    ASSERT_EQ(UInt("0x1000000000000000"), test << 32);

    UInt test2("0x1234567812345678");
    ASSERT_EQ(UInt("0x12345678123456780"), test2 << 4);
    ASSERT_EQ(UInt("0X2468ACF02468ACF00"), test2 << 5);
    ASSERT_EQ(UInt("0x123456781234567800"), test2 << 8);
    ASSERT_EQ(UInt("0x123456781234567800000000"), test2 << 32);
    ASSERT_EQ(UInt("0X2468ACF02468ACF0000000000"), test2 << 37);
    ASSERT_EQ(UInt("0x12345678123456780000000000000000"), test2 << 64);
    ASSERT_EQ(UInt("0x123456781234567800000000000000000000000000000000"), test2 << 128);
    ASSERT_EQ(UInt("0x123456781234567800000000000000000000000000000000"), test2 << 128);

    test2 <<= 128;
    ASSERT_EQ(UInt("0x123456781234567800000000000000000000000000000000"), test2);

    UInt test3 = 0x1;
    ASSERT_EQ(UInt("0x100000000"), test3 << 32);
    ASSERT_EQ(UInt("0x10000000000000000"), test3 << 64);
    ASSERT_EQ(UInt("0x100000000000000000000000000000000"), test3 << 128);
    ASSERT_EQ(UInt("0x10000000000000000000000000000000000000000000000000000000000000000"), test3 << 256);

    for (size_t shift = 0; shift < 1000; ++shift) {
        ASSERT_EQ(test3, (test3 << shift) >> shift);
    }
    test3 = UInt("0x1234567123456712345671234567123456712345671234567");
    for (size_t shift = 0; shift < 1000; ++shift) {
        ASSERT_EQ(test3, (test3 << shift) >> shift);
    }
}

TEST(UInt, ShiftRight)
{
    UInt test("0x10000000");
    ASSERT_EQ(UInt("0x10000000"), test >> 0);
    ASSERT_EQ(UInt("0x8000000"), test >> 1);
    ASSERT_EQ(UInt("0x1000000"), test >> 4);
    ASSERT_EQ(UInt("0x1000"), test >> 16);
    ASSERT_EQ(UInt("0"), test >> 32);

    UInt test2("0x1234567812345678");
    ASSERT_EQ(UInt("0x123456781234567"), test2 >> 4);
    ASSERT_EQ(UInt("0x91a2b3c091a2b3"), test2 >> 5);
    ASSERT_EQ(UInt("0x12345678123456"), test2 >> 8);
    ASSERT_EQ(UInt("0x12345678"), test2 >> 32);
    ASSERT_EQ(UInt("0x91a2b3"), test2 >> 37);

    UInt test3("0x123456781234567800000000000000000000000000000000");
    ASSERT_EQ(UInt("0x123456781234567"), test3 >> 132);
    ASSERT_EQ(UInt("0x91a2b3c091a2b3"), test3 >> 133);
    ASSERT_EQ(UInt("0x12345678123456"), test3 >> 136);
    ASSERT_EQ(UInt("0x12345678"), test3 >> 160);
    ASSERT_EQ(UInt("0x91a2b3"), test3 >> 165);

    test3 >>= 165;
    ASSERT_EQ(UInt("0x91a2b3"), test3);
}

TEST(UInt, Base10String)
{
    UInt zero("");
    ASSERT_TRUE(zero == 0);
    ASSERT_EQ("0", zero.toString());
    ASSERT_EQ(0, zero.size());

    zero = UInt("0");
    ASSERT_TRUE(zero == 0);
    ASSERT_EQ("0", zero.toString());
    ASSERT_EQ(0, zero.size());

    UInt test("256");
    ASSERT_EQ("256", test.toString());
    ASSERT_EQ("0X100", test.toString(16));

    UInt a("10000000000");
    ASSERT_EQ("0X2540BE400", a.toString(16));

    UInt rsa_100_a("37975227936943673922808872755445627854565536638199");
    UInt rsa_100_b("40094690950920881030683735292761468389214899724061");
    ASSERT_EQ("37975227936943673922808872755445627854565536638199", rsa_100_a.toString());
    ASSERT_EQ("40094690950920881030683735292761468389214899724061", rsa_100_b.toString());
    ASSERT_EQ("0X19FBD41D69AA3D86009A967DB3379C63CD501F24F7", rsa_100_a.toString(16));
    ASSERT_EQ("0X1B6F141F98EEB619BC0360220160A5F75EA07CDF1D", rsa_100_b.toString(16));
}

TEST(UInt, Base16String)
{
    UInt zero;
    ASSERT_EQ("0X0", zero.toString(16));
    ASSERT_EQ(0, zero.size());
    UInt test("ABCDABCD");
    ASSERT_EQ("0XABCDABCD", test.toString(16));
}

TEST(UInt, ErrorConditions)
{
    ASSERT_THROW(new UInt("TEST", 3), large_numbers::Error);
    ASSERT_THROW(UInt().toString(3), large_numbers::Error);
    ASSERT_THROW(UInt("-3"), large_numbers::Error);
    ASSERT_THROW(UInt("prime"), large_numbers::Error);
}

TEST(UInt, Division)
{
    UInt a(7);
    UInt b(2);
    a /= b;
    ASSERT_EQ(UInt(3), a);
    ASSERT_EQ(UInt(1), a % b);

    a = 7;
    b = 2;
    UInt c = a / b;
    ASSERT_EQ(UInt(3), c);

    UInt k("24682468246824682468246824682468", 16);
    UInt x("12341234123412341234123412341234", 16);
    c = k / x;
    ASSERT_EQ(UInt(2), c);

    c = k / 2;
    ASSERT_EQ(x, c);

    ASSERT_EQ(a, a / 1);
    ASSERT_EQ(b, b / 1);
    ASSERT_EQ(c, c / 1);
    ASSERT_EQ(k, k / 1);

    int return_code;
    for (auto i = 0; i < 10; ++i) {
        UInt r1 = large_numbers::rand();
        UInt r2 = large_numbers::rand();
        UInt r1_r2 = r1 * r2;
        std::string command = "python -c 'print(" + r1_r2.toString() + " // " + r2.toString() + ")'";
        std::string result = executeCommand(command, return_code);
        ASSERT_EQ(0, return_code) << "Failed executing command " << command;
        UInt r1b(result);
        ASSERT_EQ(r1b, r1);
    }
}

TEST(UInt, Bitwise)
{
    UInt x = 0x1001;
    ASSERT_EQ(x & 0x10, 0);
    ASSERT_EQ(x & 0x1, 0x1);
    x &= 0x1010;
    ASSERT_EQ(x, 0x1000);
}

TEST(UInt, Modulo)
{
    UInt a = 256;
    UInt b = 10;
    UInt c, d;
    UInt::div_mod(a, b, c, d);
    ASSERT_EQ(UInt(25), c);
    ASSERT_EQ(UInt(6), d);

    UInt base = 2;
    UInt exp = 10;
    UInt modulo = 1000;
    ASSERT_EQ(UInt::powerModulo(base, exp, modulo), 24);
    base.raiseToPower(10, 1000);
    ASSERT_EQ(base, 24);

    int return_code;
    for (auto i = 0; i < 10; ++i) {
        // cant go too large, otherwise it will take too long
        UInt base = 2;
        UInt exp = ::rand() % 10000;
        UInt modulo = large_numbers::rand(1);
        std::string command =
            "python -c 'print( (" + base.toString() + " ** " + exp.toString() + ") % " + modulo.toString() + ")'";
        std::string py_result_str = executeCommand(command, return_code);
        ASSERT_EQ(0, return_code) << "Failed executing command " << command;
        UInt py_result(py_result_str);
        UInt result = UInt::powerModulo(base, exp, modulo);
        ASSERT_EQ(py_result, result);
    }
}

TEST(UInt, power)
{
    UInt one = 1;
    ASSERT_EQ(UInt::pow(one, 1), 1);
    ASSERT_EQ(UInt::pow(one, 2), 1);
    ASSERT_EQ(UInt::pow(one, 0xFFFF), 1);
    one.raiseToPower(1);
    ASSERT_EQ(one, 1);
    one.raiseToPower(2);
    ASSERT_EQ(one, 1);
    one.raiseToPower(0xFFFF);
    ASSERT_EQ(one, 1);

    UInt two = 2;
    ASSERT_EQ(UInt::pow(two, 1), 2);
    ASSERT_EQ(UInt::pow(two, 2), 4);
    ASSERT_EQ(UInt::pow(two, 10), 1024);
    ASSERT_EQ(UInt::pow(two, 31), 0x80000000);
    two.raiseToPower(1);
    ASSERT_EQ(two, 2);
    two.raiseToPower(2);
    ASSERT_EQ(two, 4);
    two.raiseToPower(4);
    ASSERT_EQ(two, 0x100);

    int return_code;
    for (auto i = 0; i < 10; ++i) {
        // cant go too large, otherwise it will take too long
        UInt base = large_numbers::rand(3);
        uint32_t exp = ::rand() % 4;
        std::string command = "python -c 'print(" + base.toString() + " ** " + std::to_string(exp) + ")'";
        std::string result = executeCommand(command, return_code);
        ASSERT_EQ(0, return_code) << "Failed executing command " << command;
        UInt base_to_exp(result);
        ASSERT_EQ(base_to_exp, UInt::pow(base, exp));
    }
}

TEST(UInt, Random)
{
    // test that we have fixed seed for now
    srand(0);
    ASSERT_EQ(UInt("3637540459023997033"), large_numbers::rand(1));
    ASSERT_EQ(UInt("8408462745175416063"), large_numbers::rand(2));
    ASSERT_EQ(UInt("7085667359969386281"), large_numbers::rand(3));
    ASSERT_EQ(UInt("509856956801173727195355788088142797349857806674160671554942450503027376179805071468133774075896"),
              large_numbers::rand());
}

TEST(UInt, sqrt)
{
    UInt x = 0;
    ASSERT_EQ(x.sqrt(), 0);
    x = 1;
    ASSERT_EQ(x.sqrt(), UInt(1));
    x = 4;
    UInt result = x.sqrt();
    ASSERT_EQ(result, UInt(2));
    ASSERT_EQ(x.sqrt(), UInt(2));
    x = 25;
    ASSERT_EQ(x.sqrt(), UInt(5));
    x = UInt("4000000", 10);
    ASSERT_EQ(x.sqrt(), UInt("2000", 10));
    x = UInt("4000000000000000000000000000000000000000000000000", 10);
    ASSERT_EQ(x.sqrt(), UInt("2000000000000000000000000", 10));

    for (auto i = 0; i < 10; ++i) {
        UInt base = large_numbers::rand(4);
        UInt powered = UInt::pow(base, 2);
        UInt result = powered.sqrt();
        ASSERT_EQ(base, result);
        ASSERT_EQ(UInt::sqrt(powered), base);
    }

    for (auto i = 0; i < 10; ++i) {
        UInt powered = large_numbers::rand(4);
        UInt sqrt_num = powered.sqrt();
        ASSERT_TRUE(UInt::pow(sqrt_num, 2) <= powered);
        ASSERT_TRUE(UInt::pow(sqrt_num + 1, 2) > powered);
    }

    // TODO - python still is not 100% accurate for very large integer sqrt
    /*
    int return_code;
    for (auto i = 0; i < 10; ++i) {
        UInt num = large_numbers::rand(3);
        std::string command =
            "python -c 'import decimal; print(int(decimal.Decimal(\"" + num.toString() + "\").sqrt()))'";
        std::string result = executeCommand(command, return_code);
        ASSERT_EQ(0, return_code) << "Failed executing command " << command;
        UInt sqrt_result(result);
        ASSERT_EQ(sqrt_result, num.sqrt()) << "failed with sqrt of " << num;
    }
    */
}

TEST(UInt, BasicPrimeCheck)
{
    ASSERT_TRUE(isPrime(0));
    ASSERT_TRUE(isPrime(1));
    ASSERT_TRUE(isPrime(2));
    ASSERT_TRUE(isPrime(3));
    ASSERT_TRUE(isPrime(5));
    ASSERT_TRUE(isPrime(7));
    ASSERT_TRUE(isPrime(101));
    ASSERT_TRUE(isPrime(997));
    ASSERT_TRUE(isPrime(1031));

    ASSERT_FALSE(isPrime(4));
    ASSERT_FALSE(isPrime(6));
    ASSERT_FALSE(isPrime(8));
    ASSERT_FALSE(isPrime(9));
    ASSERT_FALSE(isPrime(10));
    ASSERT_FALSE(isPrime(1001));
}

TEST(UInt, PrimesBase)
{
    PrimesBase base(5); // 2,3,5,7,11
    ASSERT_TRUE(base.contains(2));
    ASSERT_TRUE(base.contains(3));
    ASSERT_TRUE(base.contains(5));
    ASSERT_TRUE(base.contains(10));
    ASSERT_TRUE(base.contains(4));
    ASSERT_TRUE(base.contains(40));
    ASSERT_TRUE(base.contains(2 * 3 * 5 * 7 * 9 * 2 * 3 * 5 * 7 * 9));

    ASSERT_FALSE(base.contains(13));
    ASSERT_FALSE(base.contains(29));
    ASSERT_FALSE(base.contains(2 * 3 * 5 * 7 * 17));

    base = PrimesBase(128);
    ASSERT_TRUE(base.contains(13));
    UInt candidate = 1;
    for (int i = 1; i < 100; ++i) {
        candidate *= (128 - i);
    }
    ASSERT_TRUE(base.contains(candidate));
    ASSERT_FALSE(base.contains(candidate * 1031));
}

TEST(UInt, gcd)
{
    ASSERT_EQ(UInt::gcd(2, 2), 2);
    ASSERT_EQ(UInt::gcd(2, 3), 1);
    ASSERT_EQ(UInt::gcd(3, 2), 1);
    ASSERT_EQ(UInt::gcd(4, 2), 2);
    ASSERT_EQ(UInt::gcd(2, 4), 2);
    ASSERT_EQ(UInt::gcd(20, 36), 4);
    ASSERT_EQ(UInt::gcd(36, 48), 12);

    UInt a = 36;
    ASSERT_EQ(a.gcdWith(48), 12);
}

TEST(UInt, lcm)
{
    ASSERT_EQ(UInt::lcm(2, 2), 2);
    ASSERT_EQ(UInt::lcm(2, 3), 6);
    ASSERT_EQ(UInt::lcm(3, 2), 6);
    ASSERT_EQ(UInt::lcm(4, 2), 4);
    ASSERT_EQ(UInt::lcm(2, 4), 4);
    ASSERT_EQ(UInt::lcm(20, 36), 180);
    ASSERT_EQ(UInt::lcm(36, 48), 144);

    UInt a = 36;
    ASSERT_EQ(a.lcmWith(48), 144);
}
