#include "base10_cache.h"
#include "consts.h"
#include "uint.h"

namespace large_numbers
{
    Base10Cache::Base10Cache()
    {
        int digit_pos = 0;
        UInt base10_num(1);
        for (; digit_pos < MAX_DECIMAL_DIGITS; ++digit_pos, base10_num = base10_num * 10) {
            for (int digit_value = 0; digit_value < 10; ++digit_value) {
                _cache[makeKey(digit_pos, digit_value)] = base10_num * digit_value;
            }
        }
    }

    UInt Base10Cache::get(uint32_t digit_pos, uint32_t digit_value)
    {
        return _cache.at(makeKey(digit_pos, digit_value));
    }

    uint32_t Base10Cache::makeKey(uint32_t digit_pos, uint32_t digit_value) { return digit_pos << 16 | digit_value; }
    Base10Cache base10Cache;
} // namespace large_numbers