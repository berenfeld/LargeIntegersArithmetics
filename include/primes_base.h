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
        const std::vector<uint32_t> &getPrimes() { return _primes; }
        uint32_t getPrime(size_t index) const { return _primes.at(index); }

      private:
        std::vector<uint32_t> _primes;
        std::vector<LN_BLOCK_TYPE> _products; // products of all primes in base for contains check
    };
} // namespace large_numbers