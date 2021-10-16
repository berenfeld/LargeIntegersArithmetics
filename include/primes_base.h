#include "uint.h"

namespace large_numbers
{

    class PrimesBase
    {
      public:
        PrimesBase(size_t size);
        bool contains(const UInt &value) const;

      private:
        std::vector<uint32_t> _primes;
        UInt _product; // product of all primes in base for contains check
    };
} // namespace large_numbers