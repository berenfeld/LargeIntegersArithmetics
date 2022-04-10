#include "uint.h"

namespace large_numbers
{

    class PrimesBase
    {
      public:
        PrimesBase(size_t size);
        bool contains(const UInt &value, UInt &reminder) const;
        bool contains(const UInt &value) const;
        size_t size() const { return _primes.size(); }
        LN_BLOCK_TYPE getPrime(size_t index) const { return _primes.at(index); }
        LN_BLOCK_TYPE topPrime() const { return _primes.at(_primes.size() - 1); }
        const std::vector<LN_BLOCK_TYPE> &getPrimes() const { return _primes; }
        std::vector<UInt> getPrimesAsUInts() const;
        LN_BLOCK_TYPE getRandPrime() const;
        size_t products() const { return _products.size(); }
        UInt product() const { return _product; }

      private:
        std::vector<LN_BLOCK_TYPE> _primes;
        std::vector<LN_BLOCK_TYPE> _products; // products of all primes in base for contains check
        UInt _product;
    };
} // namespace large_numbers