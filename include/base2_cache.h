#pragma once

#include "uint.h"
#include <unordered_map>

namespace large_numbers
{
    class Base2Cache
    {
      public:
        Base2Cache();
        UInt get(uint32_t digit_pos);

      private:
        uint32_t makeKey(uint32_t digit_pos);
        std::unordered_map<uint32_t, UInt, UInt::UIntHash> _cache;
    };

    /**
     * @brief The default base 2 cache, holding binary numbers of the form 1000000
     * up to constexpr binary digits
     *
     */
    extern Base2Cache base2Cache;
} // namespace large_numbers