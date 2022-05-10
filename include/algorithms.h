#include "uint.h"

namespace large_numbers
{
    /**
     * @brief
     *
     * @param n - number to factor
     * @param c - seed. if not set, use a random value
     * @param timeout_usecs - give up after elapsed time
     * @return UInt - a factor of n.1 if not found
     * based on https://www.geeksforgeeks.org/pollards-rho-algorithm-prime-factorization/
     */
    UInt rhoFactorization(UInt n, uint32_t c = 0, uint32_t timeout_usecs = 100 * 1000);

    /**
     * @brief optimized compute of the product of all the given values
     *
     * @param values
     * @return UInt
     */
    std::vector<std::vector<UInt>> productTree(const std::vector<UInt> &values);

    UInt product(const std::vector<UInt> &values);

    std::vector<UInt> remainderTree(UInt n, const std::vector<UInt> &x);

} // namespace large_numbers