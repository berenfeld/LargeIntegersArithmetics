#include "primes_base.h"
#include "uint.h"
#include <ctime>
#include <iostream>
#include <list>
#include <spdlog/spdlog.h>

using namespace large_numbers;

int main()
{
    std::srand(std::time(nullptr));
    UInt rsa_100(
        "1522605027922533360535618378132637429718068114961380688657908494580122963258952897654000350692006139");
    spdlog::info("Factoring {}", rsa_100.toString());

    UInt rsa_100_sqrt = rsa_100.sqrt() + 1;
    spdlog::info("RSA-100 sqrt {}", rsa_100_sqrt.toString());

    PrimesBase base(64);
    spdlog::info("Base size {} top prime {} products {} product {}", base.size(), base.topPrime(), base.products(),
                 base.product().toString());

    UInt candidate = rsa_100_sqrt;
    auto start = std::chrono::steady_clock::now();
    uint32_t elapsed;
    const uint32_t timeout_usecs = 600 * 1000 * 1000;
    size_t tested = 0;
    size_t smooth = 0;
    do {
        UInt test = UInt::pow(candidate, 2) - rsa_100;

        SPDLOG_DEBUG("testing {}", test.toString());

        if (base.contains(test)) {
            SPDLOG_INFO("test {} is smooth", test.toString());
            ++smooth;
        }

        SPDLOG_DEBUG("tested {}", test.toString());

        ++candidate;
        ++tested;
        if ((tested % 1000) == 0) {
            SPDLOG_INFO("tested {} candidates so far", tested);
        }
        elapsed =
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count();
    } while (elapsed < timeout_usecs);

    SPDLOG_INFO("tested {} candidates in {} usecs and found {} smooth", tested, elapsed, smooth);
}
