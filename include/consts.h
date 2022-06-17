#pragma once

#include <limits>

#define LN_BLOCK_TYPE uint64_t
#define LN_SUM_MUL_BLOCK_TYPE __uint128_t
#define LN_BITS_IN_BLOCK (sizeof(LN_BLOCK_TYPE) * 8)
#define LN_MAX_RAND_UINT_BITS 512
#define LN_MAX_RAND_UINT_BLOCKS (LN_MAX_RAND_UINT_BITS / LN_BITS_IN_BLOCK)
#define LN_HEX_DIGITS_IN_BLOCK (sizeof(LN_BLOCK_TYPE) * 2)
#define LN_MAX_BLOCK_VALUE (std::numeric_limits<LN_BLOCK_TYPE>::max())
