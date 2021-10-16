#include "base2_cache.h"
#include "consts.h"
#include "uint.h"

namespace large_numbers
{
    Base2Cache::Base2Cache()
    {
        int digit_pos = 0;
        UInt base2_num(1);
        for (; digit_pos < MAX_BINARY_DIGITS; ++digit_pos, base2_num = base2_num << 1) {
            _cache[digit_pos] = base2_num;
        }
    }

    UInt Base2Cache::get(size_t digit_pos) { return _cache.at(digit_pos); }

    Base2Cache base2Cache;
} // namespace large_numbers