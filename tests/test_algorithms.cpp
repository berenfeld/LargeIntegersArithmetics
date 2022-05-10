#include "algorithms.h"
#include "cerror.h"
#include "primes_base.h"
#include "uint.h"
#include "utils.h"
#include <gtest/gtest.h>

using namespace large_numbers;

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