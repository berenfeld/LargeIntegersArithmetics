#pragma once

#include "uint.h"
#include <unordered_map>

namespace large_numbers
{
    class Base2Cache
    {
      public:
        Base2Cache();
        UInt get(size_t digit_pos);

      private:
        size_t makeKey(size_t digit_pos);
        std::unordered_map<size_t, UInt, UInt::UIntHash> _cache;
    };

    /**
     * @brief The default base 2 cache, holding binary numbers of the form 1000000
     * up to constexpr binary digits
     *
     */
    extern Base2Cache base2Cache;
} // namespace large_numbers