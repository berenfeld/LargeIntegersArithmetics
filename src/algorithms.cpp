#include "algorithms.h"
#include "utils.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <math.h>
#include <numeric>
#include <spdlog/spdlog.h>
#include <vector>

namespace large_numbers
{
    UInt karatsuba(const UInt &n1, const UInt &n2)
    {
        if ((n1.size() <= 1) || (n2.size() <= 1)) {
            return n1.naiveMultiplyWith(n2);
        }
        const size_t min_size = std::min(n1.size(), n2.size());
        const size_t split_size = static_cast<size_t>(std::ceil(min_size / 2));
        const UInt low1 = n1.reduceToLowBlocks(split_size);
        const UInt high1 = n1.reduceToHighBlocks(n1.size() - split_size);
        const UInt low2 = n2.reduceToLowBlocks(split_size);
        const UInt high2 = n2.reduceToHighBlocks(n2.size() - split_size);

        const UInt z0 = karatsuba(low1, low2);
        const UInt z1 = karatsuba(low1 + high1, low2 + high2);
        const UInt z2 = karatsuba(high1, high2);

        return (z2 << (LN_BITS_IN_BLOCK * split_size * 2)) + ((z1 - z2 - z0) << (LN_BITS_IN_BLOCK * split_size)) + z0;
    }
    UInt pollardPMinusOneFactorization(UInt n, uint32_t timeout_usecs)
    {
        auto start = std::chrono::steady_clock::now();
        uint32_t elapsed = 0;
        size_t bits = 2;
        UInt result;
        UInt M = 2;
        do {
            const uint32_t B = 0x1ULL << bits;
            const std::vector<uint32_t> new_values = range(B / 2, B);
            const UInt M1 = lcm(new_values);
            M = UInt::lcm(M, M1);
            result = UInt::gcd(UInt::powerModulo(2, M, n) - 1, n);
            if (result != 1) {
                return result;
            }
            ++bits;
            elapsed =
                std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count();
        } while (elapsed < timeout_usecs);
        return result;
    }

    std::vector<uint32_t> range(uint32_t end) { return range(0, end); }
    std::vector<uint32_t> range(uint32_t begin, uint32_t end)
    {
        std::vector<uint32_t> result(end - begin);
        std::iota(std::begin(result), std::end(result), begin);
        return result;
    }

    UInt gcd(const std::vector<uint32_t> &values)
    {
        if (values.empty()) {
            return 1;
        }
        UInt result = values[0];
        for (size_t idx = 1; idx < values.size(); ++idx) {
            result = UInt::gcd(result, values[idx]);
        }
        return result;
    }

    UInt lcm(const std::vector<uint32_t> &values)
    {
        if (values.empty()) {
            return 1;
        }
        UInt result = values[0];
        for (size_t idx = 1; idx < values.size(); ++idx) {
            result = UInt::lcm(result, values[idx]);
        }
        return result;
    }

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
    std::vector<std::vector<UInt>> productTree(const std::vector<UInt> &values)
    {
        std::vector<std::vector<UInt>> result_tree;
        std::vector<UInt> results(values);
        result_tree.push_back(values);
        while (results.size() > 1) {
            std::vector<UInt> intermidiate_results;
            for (size_t index = 0; index < results.size() - 1; index += 2) {
                intermidiate_results.push_back(results[index] * results[index + 1]);
            }
            if (results.size() % 2) {
                intermidiate_results.push_back(results[results.size() - 1]);
            }
            result_tree.push_back(intermidiate_results);
            results = intermidiate_results;
        }
        return result_tree;
    }

    UInt product(const std::vector<UInt> &values)
    {
        auto product_tree = productTree(values);
        auto last = product_tree[product_tree.size() - 1];
        if (last.empty()) {
            return 1;
        }
        return last[0];
    }

    std::vector<UInt> remainderTree(UInt n, const std::vector<UInt> &x)
    {
        auto tree = productTree(x);
        std::vector<UInt> result(x.size());
        result[0] = n;
        UInt q, r;
        for (auto it = tree.rbegin(); it != tree.rend(); ++it) {
            const std::vector<UInt> &t = *it;
            for (int idx = t.size() - 1; idx >= 0; --idx) {
                UInt::div_mod(result[idx / 2], t[idx], q, r);
                result[idx] = r;
            }
        }
        return result;
    }

    UInt fermatFactorization(UInt n, uint32_t timeout_usecs)
    {
        if (n <= 1) {
            return n;
        }
        if (n.bit(0) == 0) {
            return 2;
        }
        auto start = std::chrono::steady_clock::now();
        uint32_t elapsed = 0;
        UInt a = n.sqrt();
        if (UInt::pow(a, 2) < n) {
            ++a;
        }
        UInt t;
        do {
            t = UInt::pow(a, 2) - n;
            if (t.sqrt().raiseToPower(2) == t) {
                break;
            }
            ++a;
            elapsed =
                std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count();
            if (elapsed > timeout_usecs) {
                return 1;
            }
        } while (1);
        UInt b = t.sqrt();
        return a - b;
    }
} // namespace large_numbers