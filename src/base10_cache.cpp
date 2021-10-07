#include "base10_cache.h"
#include "consts.h"
#include "uint.h"
#include <unordered_map>

namespace large_numbers
{
    namespace base10_cache
    {
        std::unordered_map<uint32_t, UInt, UInt::UIntHash> _cache;

        uint32_t makeKey(uint32_t digit_pos, uint32_t digit_value)
        {
            return digit_pos << 16 | digit_value;
        }

        void initCache()
        {
            if (!_cache.empty())
            {
                return;
            }
            int digit_pos = 0;
            UInt base10_num(1);
            for (; digit_pos < MAX_DECIMAL_DIGITS;
                 ++digit_pos, base10_num = base10_num * 10)
            {
                for (int digit_value = 0; digit_value < 10; ++digit_value)
                {
                    _cache[makeKey(digit_pos, digit_value)] = base10_num * digit_value;
                }
            }
        }

        UInt getUint(uint32_t digit_pos, uint32_t digit_value)
        {
            return _cache.at(makeKey(digit_pos, digit_value));
        }
    } // namespace base10_cache
} // namespace large_numbers