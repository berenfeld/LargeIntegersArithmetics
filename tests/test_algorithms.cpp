#include "algorithms.h"
#include "cerror.h"
#include "primes_base.h"
#include "uint.h"
#include "utils.h"
#include <gtest/gtest.h>

using namespace large_numbers;

TEST(Algorithms, Range)
{
    ASSERT_EQ(range(5), std::vector<uint32_t>({0, 1, 2, 3, 4}));
    ASSERT_EQ(range(1, 4), std::vector<uint32_t>({1, 2, 3}));
}

TEST(Algorithms, Gcd)
{
    ASSERT_EQ(gcd({}), 1);
    ASSERT_EQ(gcd({5}), 5);
    ASSERT_EQ(gcd({6, 10}), 2);
    ASSERT_EQ(gcd({6, 10, 36}), 2);
    ASSERT_EQ(gcd({8, 32, 4}), 4);
    ASSERT_EQ(gcd({6, 10, 4}), 2);
    ASSERT_EQ(gcd(range(1, 10)), 1);
}

TEST(Algorithms, Lcm)
{
    ASSERT_EQ(lcm({}), 1);
    ASSERT_EQ(lcm({5}), 5);
    ASSERT_EQ(lcm({6, 10}), 30);
    ASSERT_EQ(lcm({6, 10, 4}), 60);
    ASSERT_EQ(lcm(range(1, 10)), 2520);
}

TEST(Algorithms, RhoFactorization)
{
    ASSERT_EQ(rhoFactorization(1), 1);
    ASSERT_EQ(rhoFactorization(15), 5);
    ASSERT_EQ(rhoFactorization(17 * 19), 17);

    PrimesBase base(1000);
    ASSERT_EQ(rhoFactorization(base.getPrime(999) * base.getPrime(998)), base.getPrime(999));
    ASSERT_EQ(rhoFactorization(base.getPrime(998) * base.getPrime(997)), base.getPrime(998));
    ASSERT_EQ(rhoFactorization(base.getPrime(997) * base.getPrime(996)), base.getPrime(996));

    ASSERT_EQ(rhoFactorization(base.getPrime(995) * base.getPrime(994), 0, 1), 1);
}

TEST(Algorithms, ProductTree)
{
    ASSERT_EQ(product({2}), 2);
    ASSERT_EQ(product({}), 1);

    large_numbers::PrimesBase base(2);
    std::vector<UInt> values = base.getPrimesAsUInts();
    ASSERT_EQ(product(values), 6);

    base = large_numbers::PrimesBase(5);
    values = base.getPrimesAsUInts();
    ASSERT_EQ(product(values), 2310);

    ASSERT_EQ(product({2, 2, 2, 2, 2, 2, 2, 2, 2, 2}), 1024);
    ASSERT_EQ(product({2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}), 2048);

    std::vector<std::vector<UInt>> result = {{1, 2, 3, 4}, {2, 12}, {24}};
    ASSERT_EQ(productTree(result[0]), result);

    result = {{1, 2, 3, 4, 5}, {2, 12, 5}, {24, 5}, {120}};
    ASSERT_EQ(productTree(result[0]), result);
}

TEST(Algorithms, RemainderTree)
{
    UInt n = 8675309;
    std::vector<UInt> x{11, 13, 17, 19, 23};
    std::vector<UInt> result = remainderTree(n, x);
    ASSERT_EQ(result, std::vector<UInt>({5, 6, 5, 4, 8}));
}

TEST(Algorithms, Fermat)
{
    ASSERT_EQ(fermatFactorization(1), 1);
    ASSERT_EQ(fermatFactorization(15), 3);
    ASSERT_EQ(fermatFactorization(18), 2);
    ASSERT_EQ(fermatFactorization(17), 1);
    ASSERT_EQ(fermatFactorization(6557), 79);
    UInt n("115792089237316195423570985008721211221144628262713908746538761285902758367353");
    ASSERT_EQ(fermatFactorization(n), UInt("340282366920938463463374607431817146293"));
    UInt rsa_100(
        "1522605027922533360535618378132637429718068114961380688657908494580122963258952897654000350692006139");
    ASSERT_EQ(fermatFactorization(rsa_100), 1);
}