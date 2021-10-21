#include "primes_base.h"
#include "utils.h"

namespace large_numbers
{
    PrimesBase::PrimesBase(size_t size)
    {
        uint32_t num = 2;
        UInt product = 1;
        size_t included_primes = 0;
        while (included_primes < size) {
            if (isPrime(num)) {
                product *= num;
                if (product.size() == 2) {
                    // store the products in 1-block UInts
                    product /= num;
                    _products.push_back(product.block(0));
                    product = num;
                }
                ++included_primes;
            }
            ++num;
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