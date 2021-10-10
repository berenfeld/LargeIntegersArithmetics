#include "primes_base.h"
#include "utils.h"

namespace large_numbers
{
    PrimesBase::PrimesBase(uint32_t size)
    {
        uint32_t num = 2;

        while (_primes.size() < size) {
            if (isPrime(num)) {
                _primes.push_back(num);
            }
            ++num;
        }
    }

    bool PrimesBase::contains(const UInt &value) const
    {
        UInt remaining = value;
        UInt q, r;
        for (size_t i = 0; i < _primes.size(); ++i) {
            do {
                UInt::div_mod(remaining, _primes[i], q, r);
                if (r == 0) {
                    remaining = q;
                }
                if (remaining == 1) {
                    return true;
                }
            } while (r == 0);
        }
        return false;
    }
} // namespace large_numbers