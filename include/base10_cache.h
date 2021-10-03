#pragma once

#include "uint.h"

namespace large_numbers
{
    namespace base10_cache
    {
        void initCache();

        UInt getUint(uint32_t digit_pos, uint32_t digit_value);
    }
}