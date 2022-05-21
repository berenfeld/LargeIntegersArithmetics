#include "uint.h"

namespace large_numbers
{

    class PrimesBase
    {
      public:
        PrimesBase(size_t size);
        UInt findFactor(const UInt &n) const;
        bool contains(const UInt &value, UInt &reminder) const;
        bool contains(const UInt &value) const;
        uint32_t getPrime(uint32_t index) const { return _primes.at(index); }
        const std::vector<uint32_t> &getPrimes() const { return _primes; }
        std::vector<UInt> getPrimesAsUInts() const;

      private:
        std::vector<uint32_t> _primes;
        std::vector<LN_BLOCK_TYPE> _products; // products of all primes in base for contains check
    };
} // namespace large_numbers