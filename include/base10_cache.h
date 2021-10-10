#pragma once

#include "uint.h"
#include <unordered_map>

namespace large_numbers
{
    class Base10Cache
    {
      public:
        Base10Cache();
        UInt get(uint32_t digit_pos, uint32_t digit_value);

      private:
        uint32_t makeKey(uint32_t digit_pos, uint32_t digit_value);
        std::unordered_map<uint32_t, UInt, UInt::UIntHash> _cache;
    };

    /**
     * @brief The default base10 cache, holding decimal numbers of the form X000000
     * where X is in 1..9 , up to MAX_DECIMAL_DIGITS decimal digits
     *
     */
    extern Base10Cache base10Cache;
} // namespace large_numbers