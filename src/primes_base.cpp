#include "primes_base.h"
#include "utils.h"

namespace large_numbers
{
    PrimesBase::PrimesBase(uint32_t size)
    {
        uint32_t num = 2;
        _product = 1;
        while (_primes.size() < size) {
            if (isPrime(num)) {
                _primes.push_back(num);
                _product *= num;
            }
            ++num;
        }
    }

    bool PrimesBase::contains(const UInt &value) const
    {
        UInt remaining_product = _product;
        UInt remaining_value = value;
        do {
            UInt gcd_result = UInt::gcd(remaining_product, remaining_value);
            if (gcd_result == remaining_value) {
                return true;
            }
            if (gcd_result == 1) {
                return false;
            }
            remaining_value /= gcd_result;
            remaining_product = gcd_result;
        } while (true);
        return false;
    }
} // namespace large_numbers