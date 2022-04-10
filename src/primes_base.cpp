#include "primes_base.h"
#include "cerror.h"
#include "utils.h"
#include <fstream>
#include <iostream>

namespace large_numbers
{
    PrimesBase::PrimesBase(size_t size)
    {
        const std::string primes_file_name("primes.list");
        std::ifstream primes_file(primes_file_name);
        LN_ASSERT(primes_file.is_open(), "failed to open file " + primes_file_name);
        size_t added_primes = 0;
        uint32_t next_prime;
        UInt product = 1;
        _product = 1;

        while (added_primes < size) {
            primes_file >> next_prime;
            _primes.push_back(next_prime);
            product *= next_prime;
            _product *= next_prime;
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
        do {
            UInt gcd_result = UInt::gcd(_product, reminder);
            reminder /= gcd_result;
            if (reminder == 1) {
                return true;
            }
            if (gcd_result == 1) {
                return false;
            }
        } while (true);

        return false;
    }

    bool PrimesBase::contains(const UInt &value) const
    {
        UInt reminder_unused;
        return contains(value, reminder_unused);
    }

    std::vector<UInt> PrimesBase::getPrimesAsUInts() const
    {
        std::vector<UInt> result;
        for (uint32_t prime : _primes) {
            result.push_back(prime);
        }
        return result;
    }

    LN_BLOCK_TYPE PrimesBase::getRandPrime() const { return _primes.at(::rand() % _primes.size()); }

} // namespace large_numbers