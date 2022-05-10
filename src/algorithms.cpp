#include "algorithms.h"
#include "utils.h"
#include <chrono>
#include <math.h>
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
} // namespace large_numbers