#include "uint.h"

namespace large_numbers
{

    class PrimesBase
    {
      public:
        PrimesBase(uint32_t size);
        bool contains(const UInt &value) const;

      private:
        std::vector<uint32_t> _primes;
    };
} // namespace large_numbers