#include "primes_base.h"
#include "cerror.h"
#include "utils.h"
#include <fstream>

namespace large_numbers
{
    PrimesBase::PrimesBase(size_t size)
    {
        const std::string primes_file_name("primes.list");
        std::ifstream primes_file(primes_file_name);
        LN_ASSERT(primes_file.is_open(), "failed to open file " + primes_file_name);
        size_t added_primes = 0;
        int next_prime;
        UInt product = 1;

        while (added_primes < size) {
            primes_file >> next_prime;
            product *= next_prime;
            if (product.size() == 2) {
                // store the products in 1-block UInts
                product /= next_prime;
                _products.push_back(product.block(0));
                product = next_prime;
            }
            ++added_primes;
        }
        // push last product
        _products.push_back(product.block(0));
    }

    bool PrimesBase::contains(const UInt &value, UInt &reminder) const
    {
        reminder = value;
        for (size_t i = 0; i < _products.size(); ++i) {
            UInt remaining_product = _products[i];
            do {
                UInt gcd_result = UInt::gcd(remaining_product, reminder);
                reminder /= gcd_result;
                if (reminder == 1) {
                    return true;
                }
                if (gcd_result == 1) {
                    break;
                }
                remaining_product = gcd_result;
            } while (true);
        }
        return false;
    }

    bool PrimesBase::contains(const UInt &value) const
    {
        UInt reminder_unused;
        return contains(value, reminder_unused);
    }
} // namespace large_numbers