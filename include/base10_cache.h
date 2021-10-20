#pragma once

#include "uint.h"
#include <unordered_map>

namespace large_numbers
{
    class Base10Cache
    {
      public:
        Base10Cache();
        UInt get(size_t digit_pos, size_t digit_value);

      private:
        void extendTo(size_t max_digit_pos);
        size_t makeKey(size_t digit_pos, size_t digit_value);
        std::unordered_map<size_t, UInt, UInt::UIntHash> _cache;
        size_t max_digit_pos_cached;
    };

    /**
     * @brief The default base10 cache, holding decimal numbers of the form
     * X000000 where X is in 1..9 , up to MAX_DECIMAL_DIGITS decimal digits
     *
     */
    extern Base10Cache base10Cache;
} // namespace large_numbers