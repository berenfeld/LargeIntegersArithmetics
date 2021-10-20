#include "base10_cache.h"
#include "consts.h"
#include "uint.h"

namespace large_numbers
{
    Base10Cache::Base10Cache() : max_digit_pos_cached(0) {}

    void Base10Cache::extendTo(size_t max_digit_pos)
    {
        UInt base10_num = UInt::pow(10, max_digit_pos_cached);
        for (size_t digit_pos = max_digit_pos_cached; digit_pos < max_digit_pos;
             ++digit_pos, base10_num = base10_num * 10) {
            for (int digit_value = 0; digit_value < 10; ++digit_value) {
                _cache[makeKey(digit_pos, digit_value)] = base10_num * digit_value;
            }
        }
        max_digit_pos_cached = max_digit_pos;
    }

    UInt Base10Cache::get(size_t digit_pos, size_t digit_value)
    {
        auto found = _cache.find(makeKey(digit_pos, digit_value));
        if (found == _cache.end()) {
            extendTo(digit_pos + 1);
            found = _cache.find(makeKey(digit_pos, digit_value));
        }
        return found->second;
    }

    size_t Base10Cache::makeKey(size_t digit_pos, size_t digit_value) { return digit_pos << 16 | digit_value; }
    Base10Cache base10Cache;
} // namespace large_numbers