#include "algorithms.h"
#include "utils.h"
#include <chrono>
#include <vector>

namespace large_numbers
{
    UInt rhoFactorization(UInt n, uint32_t c, uint32_t timeout_usecs)
    {
        auto start = std::chrono::steady_clock::now();
        if (c == 0) {
            c = ::rand();
        }
        UInt c1 = c;
        c1 = c1 % n;
        UInt x = rand(1);
        UInt y = x;
        uint32_t elapsed = 0;

        do {
            x = (x.raiseToPower(2) + c1) % n;
            y = ((y.raiseToPower(2) + c1).raiseToPower(2) + c1) % n;

            UInt diff = x > y ? x - y : y - x;
            UInt gcd = UInt::gcd(diff, n);
            if (gcd == n) {
                // not found
                return 1;
            }
            if (gcd != 1) {
                return gcd;
            }
            elapsed =
                std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count();
        } while (elapsed < timeout_usecs);
        return 1;
    }

    /**
     * @brief optimized compute of the product of all the given values
     *
     * @param values
     * @return UInt
     */
    UInt product(const std::vector<UInt> &values)
    {
        if (values.empty()) {
            return 1;
        }
        std::vector<UInt> results(values);
        size_t results_size = results.size();
        while (results_size > 1) {
            size_t middle = results_size / 2;
            size_t parity = results_size % 2;
            for (size_t index = 0; index < middle; ++index) {
                results[index] *= results[index + middle + parity];
            }
            results_size = middle + parity;
        }
        return results.at(0);
    }
} // namespace large_numbers