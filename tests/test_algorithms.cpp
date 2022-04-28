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