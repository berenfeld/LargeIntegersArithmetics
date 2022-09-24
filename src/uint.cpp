#include "uint.h"
#include "algorithms.h"
#include "base2_cache.h"
#include "cerror.h"
#include "consts.h"
#include "utils.h"
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <sstream>
#include <unordered_set>

namespace large_numbers
{
    UInt::UInt() {}

    UInt::UInt(LN_BLOCK_TYPE value)
    {
        if (value) {
            _values.push_back(value);
        }
    }

    UInt::UInt(const std::string &str, int base)
    {
        std::string str2 = str;
        trim(str2);
        if (base == 0) {
            base = guessBaseOf(str2);
        }
        switch (base) {
        case 10: {
            UInt result = parseBase10StringValues(str2);
            _values = result._values;
            trimZeros();
            break;
        }
        case 16: {
            parseBase16StringValues(str2, _values);
            trimZeros();
            break;
        }
        default:
            throw Error("Base not supported " + std::to_string(base) + " for : '" + str2 + "'");
            break;
        }
    }

    bool UInt::operator==(const UInt &other) const { return _values == other._values; }

    bool UInt::operator==(LN_BLOCK_TYPE value) const
    {
        if (value) {
            return size() == 1 && _values[0] == value;
        } else {
            return _values.empty();
        }
    }

    bool UInt::operator!=(const UInt &other) const { return !(*this == other); }

    bool UInt::operator!=(LN_BLOCK_TYPE value) const { return !(*this == value); }

    UInt &UInt::operator++()
    {
        *this += 1;
        return *this;
    }

    UInt &UInt::operator--()
    {
        *this -= 1;
        return *this;
    }

    UInt &UInt::operator+=(const UInt &other)
    {
        const size_t max_block = std::max(size(), other.size());
        _values.resize(max_block);
        LN_BLOCK_TYPE add_to_next_value = 0;
        size_t i = 0;
        while (i < max_block) {
            LN_SUM_MUL_BLOCK_TYPE added_value =
                static_cast<LN_SUM_MUL_BLOCK_TYPE>(_values[i]) + static_cast<LN_SUM_MUL_BLOCK_TYPE>(add_to_next_value) +
                (i < other.size() ? static_cast<LN_SUM_MUL_BLOCK_TYPE>(other._values[i]) : 0);
            _values[i] = static_cast<LN_BLOCK_TYPE>(added_value);
            add_to_next_value = added_value >> LN_BITS_IN_BLOCK;
            ++i;
        }
        if (add_to_next_value) {
            _values.push_back(add_to_next_value);
        }
        return *this;
    }

    UInt UInt::operator+(const UInt &other) const { return UInt(*this) += other; }

    UInt &UInt::operator+=(LN_BLOCK_TYPE arg)
    {
        *this += UInt(arg);
        return *this;
    }

    UInt UInt::operator+(LN_BLOCK_TYPE arg) { return UInt(*this) + UInt(arg); }

    UInt UInt::operator-(const UInt &other) const { return UInt(*this) -= other; }

    UInt &UInt::operator-=(const UInt &other)
    {
        const size_t other_size = other.size();
        UInt other_negate = other.negate();
        // negate value of other is 2^n - other - 1, where n is the number of
        // bits of other rounded up to 64. so we need to substract 2^n and add 1
        // back
        *this += other_negate;
        *this += 1;
        for (size_t i = other_size; i < _values.size(); ++i) {
            if (_values[i] != 0) {
                --_values[i];
                break;
            }
            _values[i] = LN_MAX_BLOCK_VALUE; // loan 1 from next dword
        }
        // remove trailing 0 if present
        while (_values.size() && _values[_values.size() - 1] == 0) {
            _values.pop_back();
        }
        return *this;
    }

    UInt &UInt::operator-=(LN_BLOCK_TYPE arg)
    {
        *this -= UInt(arg);
        return *this;
    }

    UInt UInt::operator-(LN_BLOCK_TYPE arg) { return UInt(*this) - UInt(arg); }

    UInt UInt::operator*(LN_BLOCK_TYPE arg) const
    {
        UInt result;
        LN_BLOCK_TYPE add_to_next_value = 0;
        LN_SUM_MUL_BLOCK_TYPE arg64 = static_cast<LN_SUM_MUL_BLOCK_TYPE>(arg);
        for (const LN_BLOCK_TYPE &value : _values) {
            LN_SUM_MUL_BLOCK_TYPE result_value = static_cast<LN_SUM_MUL_BLOCK_TYPE>(value) * arg64;
            result_value += add_to_next_value;
            result._values.push_back(static_cast<LN_BLOCK_TYPE>(result_value));
            add_to_next_value = result_value >> LN_BITS_IN_BLOCK;
        }
        if (add_to_next_value) {
            result._values.push_back(add_to_next_value);
        }
        return result;
    }

    UInt &UInt::operator*=(LN_BLOCK_TYPE arg)
    {
        *this = *this * arg;
        return *this;
    }

    void UInt::mulAdd(LN_BLOCK_TYPE arg, UInt &result, size_t add_to_block) const
    {
        LN_BLOCK_TYPE add_to_next_value = 0;
        LN_SUM_MUL_BLOCK_TYPE arg64 = static_cast<LN_SUM_MUL_BLOCK_TYPE>(arg);
        while (result._values.size() < (_values.size() + add_to_block + 1)) {
            result._values.push_back(0);
        }
        for (size_t i = 0; i < _values.size(); ++i) {
            LN_SUM_MUL_BLOCK_TYPE result_value = static_cast<LN_SUM_MUL_BLOCK_TYPE>(_values[i]) * arg64 +
                                                 result._values[i + add_to_block] + add_to_next_value;
            result._values[i + add_to_block] = static_cast<LN_BLOCK_TYPE>(result_value);
            add_to_next_value = result_value >> LN_BITS_IN_BLOCK;
        }
        int result_index = _values.size() + add_to_block;
        while (add_to_next_value) {
            LN_SUM_MUL_BLOCK_TYPE result_value =
                static_cast<LN_SUM_MUL_BLOCK_TYPE>(result._values[result_index]) + add_to_next_value;
            result._values[result_index] = static_cast<LN_BLOCK_TYPE>(result_value);
            add_to_next_value = result_value >> LN_BITS_IN_BLOCK;
            ++result_index;
        }
        result.trimZeros();
    }

    UInt UInt::operator*(const UInt &arg) const
    {
        UInt result = 0;
        for (size_t i = 0; i < arg.size(); ++i) {
            mulAdd(arg.block(i), result, i);
        }
        return result;
    }

    UInt &UInt::operator*=(const UInt &arg)
    {
        *this = *this * arg;
        return *this;
    }

    // static
    UInt UInt::pow(const UInt &base, const UInt &exp)
    {
        UInt result = 1;
        UInt base2 = base;
        UInt exp2 = exp;
        for (;;) {
            if ((exp2 & 0x1) == (0x1)) {
                result *= base2;
            }
            exp2 >>= 1;
            if (exp2 == 0) {
                break;
            }
            base2 *= base2;
        }
        return result;
    }

    UInt &UInt::raiseToPower(const UInt &exp)
    {
        *this = pow(*this, exp);
        return *this;
    }

    // static
    UInt UInt::powerModulo(const UInt &base, const UInt &exp, const UInt &modulo)
    {
        // same as power, but modulo on each step
        std::vector<UInt> powers(exp.bits());
        UInt base_power = base;
        for (size_t bit = 0; bit < exp.bits(); ++bit) {
            powers[bit] = base_power;
            base_power *= base_power;
            base_power %= modulo;
        }
        UInt result = 1;
        UInt bit_value = 0x1;
        for (size_t bit = 0; bit < exp.bits(); ++bit) {
            if ((exp & bit_value) != UInt(0)) {
                result *= powers[bit];
                result %= modulo;
            }
            bit_value <<= 1;
        }
        return result;
    }

    UInt &UInt::raiseToPower(const UInt &exp, const UInt &modulo)
    {
        *this = powerModulo(*this, exp, modulo);
        return *this;
    }

    // static
    UInt UInt::gcd(const UInt &a, const UInt &b)
    {
        if (a == 0) {
            return b;
        }
        if (b == 0) {
            return a;
        }
        if (a > b) {
            return gcd(a % b, b);
        }
        return gcd(a, b % a);
    }

    UInt UInt::gcdWith(const UInt &other) const { return gcd(*this, other); }

    // static
    UInt UInt::lcm(const UInt &a, const UInt &b) { return a * b / gcd(a, b); }

    UInt UInt::lcmWith(const UInt &other) const { return lcm(*this, other); }

    // static
    UInt UInt::sqrt(const UInt &n)
    {
        if (n < 1) {
            return n;
        }
        // start from a good guess
        LN_BLOCK_TYPE len = n.bits() >> 2;
        UInt result = UInt(1) << len;

        std::unordered_set<UInt, UIntHasher> results;
        // to find the sqrt(S)=lim(x->inf): X_(n+1) = (Xn + S/Xn)/2
        do {
            result += (n / result);
            result >>= 1;
            if (results.find(result) != results.end()) {
                break;
            }
            results.insert(result);
        } while (1);
        return result;
    }

    UInt UInt::sqrt() const
    {
        UInt result = UInt::sqrt(*this);
        return result;
    }

    UInt UInt::operator<<(size_t offset) const
    {
        const LN_BLOCK_TYPE zero_blocks = offset / LN_BITS_IN_BLOCK;
        UInt result;
        result._values.resize(this->size() + zero_blocks);
        const unsigned reminder = static_cast<unsigned>(offset % LN_BITS_IN_BLOCK);
        const LN_BLOCK_TYPE reminder_comp = (LN_BITS_IN_BLOCK - reminder);
        LN_BLOCK_TYPE carry = 0;
        for (size_t idx = 0; idx < this->size(); ++idx) {
            const LN_BLOCK_TYPE &value = this->block(idx);
            const LN_SUM_MUL_BLOCK_TYPE &value_sum = static_cast<const LN_SUM_MUL_BLOCK_TYPE &>(value);
            const LN_BLOCK_TYPE next_value = static_cast<LN_BLOCK_TYPE>((value_sum << reminder) | carry);
            carry = (value_sum >> reminder_comp);
            result._values[zero_blocks + idx] = next_value;
        }
        if (carry) {
            result._values.push_back(carry);
        }

        return result;
    }

    UInt &UInt::operator<<=(size_t offset)
    {
        *this = *this << offset;
        return *this;
    }

    UInt UInt::operator>>(size_t offset) const
    {
        UInt result(*this);
        offset = std::min(offset, result.bits());

        size_t zero_blocks = offset / LN_BITS_IN_BLOCK;
        offset -= (zero_blocks * LN_BITS_IN_BLOCK);
        result._values.erase(result._values.begin(), result._values.begin() + zero_blocks);

        result._values.push_back(0);
        for (size_t i = 0; i < result.size() - 1; ++i) {
            LN_SUM_MUL_BLOCK_TYPE value =
                (static_cast<LN_SUM_MUL_BLOCK_TYPE>(result._values[i + 1]) << LN_BITS_IN_BLOCK) | result._values[i];
            value = value >> offset;
            result._values[i] = static_cast<LN_BLOCK_TYPE>(value);
        }
        result.trimZeros();

        return result;
    }

    UInt &UInt::operator>>=(size_t offset)
    {
        *this = *this >> offset;
        return *this;
    }

    UInt UInt::operator/(const UInt &other) const
    {
        UInt q, r;
        div_mod(*this, other, q, r);
        return q;
    }

    UInt &UInt::operator/=(const UInt &other)
    {
        UInt r;
        div_mod(*this, other, *this, r);
        return *this;
    }

    UInt UInt::operator/(LN_BLOCK_TYPE other) const { return *this / UInt(other); }

    UInt &UInt::operator/=(LN_BLOCK_TYPE other)
    {
        *this /= UInt(other);
        return *this;
    }

    UInt UInt::operator%(const UInt &other) const
    {
        UInt q, r;
        div_mod(*this, other, q, r);
        return r;
    }

    UInt &UInt::operator%=(const UInt &other)
    {
        UInt q;
        div_mod(*this, other, q, *this);
        return *this;
    }

    // static
    void UInt::div_mod(const UInt &a, const UInt &b, UInt &q, UInt &r)
    {
        r = a;
        q = UInt(0);
        UInt to_sub;
        while (r >= b) {
            const size_t r_len = r.bits();
            const size_t b_len = b.bits();
            if (r_len <= b_len + 1) {
                break;
            }
            const size_t zeros = r_len - b_len - 1;
            q += base2Cache.get(zeros);
            to_sub = b << zeros;
            r -= to_sub;
        }
        while (r >= b) {
            ++q;
            r -= b;
        }
    }

    UInt UInt::operator&(const UInt &other) const
    {
        UInt result = *this;
        result &= other;
        return result;
    }

    UInt &UInt::operator&=(const UInt &other)
    {
        size_t to_block = std::min(size(), other.size());
        for (size_t block_index = 0; block_index < to_block; ++block_index) {
            _values[block_index] &= other.block(block_index);
        }
        trimZeros();
        return *this;
    }

    bool UInt::operator<(const UInt &other) const { return compare(*this, other) < 0; }
    bool UInt::operator<=(const UInt &other) const { return compare(*this, other) <= 0; }
    bool UInt::operator>(const UInt &other) const { return compare(*this, other) > 0; }
    bool UInt::operator>=(const UInt &other) const { return compare(*this, other) >= 0; }
    // static
    int8_t UInt::compare(const UInt &a, const UInt &b)
    {
        if (a.size() != b.size()) {
            return a.size() > b.size() ? 1 : -1;
        }
        for (int i = a.size() - 1; i >= 0; --i) {
            if (a.block(i) != b.block(i)) {
                return a.block(i) > b.block(i) ? 1 : -1;
            }
        }
        return 0;
    }

    std::string UInt::toString(int base) const
    {
        switch (base) {
        case 16:
            return base16StringOf(*this);
        case 10:
            return base10StringOf(*this);
        default:
            throw Error("Base not supported " + std::to_string(base));
        }
    }

    size_t UInt::size() const { return _values.size(); }
    const LN_BLOCK_TYPE &UInt::block(int i) const { return _values[i]; }
    const LN_BLOCK_TYPE &UInt::lastBlock() const { return _values[size() - 1]; }

    uint32_t UInt::bit(int i) const
    {
        uint32_t block_index = i / sizeof(LN_BLOCK_TYPE) * 8;
        uint32_t bit_index = i % sizeof(LN_BLOCK_TYPE) * 8;
        return block(block_index) & (0x1ULL << bit_index);
    }

    UInt UInt::negate() const
    {
        UInt result;
        for (LN_BLOCK_TYPE _value : _values) {
            result._values.push_back(~_value);
        }
        // trim leading zeroes
        while (result.size() && result._values[result._values.size() - 1] == 0) {
            result._values.pop_back();
        }
        return result;
    }

    void UInt::trimZeros()
    {
        while ((!_values.empty()) && _values.back() == 0) {
            _values.pop_back();
        }
    }

    size_t UInt::bits() const
    {
        if (_values.empty()) {
            return 0;
        }
        return (size() - 1) * LN_BITS_IN_BLOCK + lastBit(lastBlock());
    }

    std::size_t UIntHasher::operator()(const UInt &element) const
    {
        LN_BLOCK_TYPE ret = 0;
        for (size_t idx = 0; idx < element.size(); ++idx) {
            ret += element._values[idx];
        }
        return static_cast<std::size_t>(ret);
    }
} // namespace large_numbers