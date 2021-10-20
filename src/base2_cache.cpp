#include "base2_cache.h"
#include "consts.h"
#include "uint.h"

namespace large_numbers
{
    Base2Cache::Base2Cache() : max_digit_pos_cached(0) {}

    void Base2Cache::extendTo(size_t max_digit_pos)
    {
        UInt base2_num = 1 << max_digit_pos_cached;
        for (size_t digit_pos = max_digit_pos_cached; digit_pos < max_digit_pos;
             ++digit_pos, base2_num = base2_num << 1) {
            _cache[digit_pos] = base2_num;
        }
        max_digit_pos_cached = max_digit_pos;
    }

    UInt Base2Cache::get(size_t digit_pos)
    {
        auto found = _cache.find(digit_pos);
        if (found == _cache.end()) {
            extendTo(digit_pos);
            found = _cache.find(digit_pos);
        }
        return found->second;
    }

    Base2Cache base2Cache;
} // namespace large_numbers