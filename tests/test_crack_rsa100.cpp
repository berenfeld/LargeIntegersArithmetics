#include "algorithms.h"
#include "cerror.h"
#include "primes_base.h"
#include "uint.h"
#include "utils.h"
#include <chrono>
#include <gtest/gtest.h>

using namespace large_numbers;

bool findFactors(const UInt &n, uint32_t timeout_usecs, std::vector<UInt> &factors)
{
    // try to find a factor using all available methods until timeout expired
    UInt remainder = n;
    auto start = std::chrono::steady_clock::now();
    uint32_t elapsed = 0;

    while (remainder > 1) {
        elapsed =
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count();
        if (elapsed > timeout_usecs) {
            return false;
        };

        // try to divide with first small primes using a base proudct
        PrimesBase base(1000); // TODO find tune this
        UInt factor = base.findFactor(remainder);
        if ((factor != 1) && (factor != n)) {
            factors.push_back(factor);
            remainder /= factor;
            continue;
        }

        elapsed =
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count();
        if (elapsed > timeout_usecs) {
            return false;
        };

        // try rho factorization
        factor = rhoFactorization(remainder, timeout_usecs);
        if ((factor != 1) && (factor != n)) {
            factors.push_back(factor);
            remainder /= factor;
            continue;
        }

        elapsed =
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count();
        if (elapsed > timeout_usecs) {
            return false;
        };

        // try pollard p-1
        factor = pollardPMinusOneFactorization(remainder, timeout_usecs);
        if ((factor != 1) && (factor != n)) {
            factors.push_back(factor);
            remainder /= factor;
            continue;
        }
    }
    return true;
}

TEST(Crack, Rsa100)
{
    UInt rsa_100(
        "1522605027922533360535618378132637429718068114961380688657908494580122963258952897654000350692006139");
    const UInt rsa_100_sqrt = rsa_100.sqrt() + 1;

    UInt tested = rsa_100_sqrt;
    std::vector<UInt> factors;
    for (int i = 0; i < 1000; ++i) {
        UInt related = UInt::pow(tested, 2) - rsa_100;

        std::cout << "testing related " << related << std::endl;
        factors.clear();
        bool factored = findFactors(related, 100, factors);

        if (factored) {
            std::cout << "factored " << related << std::endl;
        }
        ++tested;
    }
}
