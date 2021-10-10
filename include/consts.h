#pragma once

namespace large_numbers
{
    static constexpr int MAX_DECIMAL_DIGITS = 256;
    static constexpr int MAX_BINARY_DIGITS = 1024;
    static constexpr int MAX_RAND_UINT_BITS = 512;
    static constexpr int MAX_RAND_UINT_BLOCKS = MAX_RAND_UINT_BITS / 32;
} // namespace large_numbers