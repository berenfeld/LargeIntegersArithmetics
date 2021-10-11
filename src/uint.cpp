#include "uint.h"
#include "base2_cache.h"
#include "error.h"
#include "utils.h"
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <sstream>

namespace large_numbers
{
    UInt::UInt() {}

    UInt::UInt(uint32_t value)
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
            break;
        }
        case 16: {
            parseBase16StringValues(str2, _values);
            break;
        }
        default:
            throw Error("Base not supported " + std::to_string(base) + " for : '" + str2 + "'");
        }
    }

    bool UInt::operator==(const UInt &other) const { return _values == other._values; }

    bool UInt::operator==(uint32_t value) const
    {
        if (value) {
            return size() == 1 && _values[0] == value;
        } else {
            return _values.empty();
        }
    }

    bool UInt::operator!=(const UInt &other) const { return !(*this == other); }

    bool UInt::operator!=(uint32_t value) const { return !(*this == value); }

    UInt &UInt::operator+=(const UInt &other)
    {
        const size_t max_block = std::max(size(), other.size());
        _values.resize(max_block);
        uint32_t add_to_next_value = 0;
        size_t i = 0;
        while (i < max_block) {
            uint64_t added_value = static_cast<uint64_t>(_values[i]) + static_cast<uint64_t>(add_to_next_value) +
                                   (i < other.size() ? static_cast<uint64_t>(other._values[i]) : 0);
            _values[i] = static_cast<uint32_t>(added_value);
            add_to_next_value = added_value >> 32;
            ++i;
        }
        if (add_to_next_value) {
            _values.push_back(add_to_next_value);
        }
        return *this;
    }

    UInt UInt::operator+(const UInt &other) const { return UInt(*this) += other; }

    UInt &UInt::operator+=(uint32_t arg)
    {
        *this += UInt(arg);
        return *this;
    }

    UInt UInt::operator+(uint32_t arg) { return UInt(*this) + UInt(arg); }

    UInt UInt::operator-(const UInt &other) const { return UInt(*this) -= other; }

    UInt &UInt::operator-=(const UInt &other)
    {
        const size_t other_size = other.size();
        UInt other_negate = other.negate();
        // negate value of other is 2^n - other - 1, where n is the number of bits of
        // other rounded up to 32. so we need to substract 2^n and add 1 back
        *this += other_negate;
        *this += 1;
        for (size_t i = other_size; i < _values.size(); ++i) {
            if (_values[i] != 0) {
                --_values[i];
                break;
            }
            _values[i] = 0xFFFFFFFF; // loan 1 from next dword
        }
        // remove trailing 0 if present
        while (_values.size() && _values[_values.size() - 1] == 0) {
            _values.pop_back();
        }
        return *this;
    }

    UInt &UInt::operator-=(uint32_t arg)
    {
        *this -= UInt(arg);
        return *this;
    }

    UInt UInt::operator-(uint32_t arg) { return UInt(*this) - UInt(arg); }

    UInt UInt::operator*(uint32_t arg) const
    {
        UInt result;
        uint32_t add_to_next_value = 0;
        uint64_t arg64 = static_cast<uint64_t>(arg);
        for (const uint32_t &value : _values) {
            uint64_t result_value = static_cast<uint64_t>(value) * arg64;
            result_value += add_to_next_value;
            result._values.push_back(static_cast<uint32_t>(result_value));
            add_to_next_value = result_value >> 32;
        }
        if (add_to_next_value) {
            result._values.push_back(add_to_next_value);
        }
        return result;
    }

    UInt &UInt::operator*=(uint32_t arg)
    {
        *this = *this * arg;
        return *this;
    }

    UInt UInt::operator*(const UInt &arg) const
    {
        UInt result;
        for (size_t i = 0; i < arg.size(); ++i) {
            UInt interm = *this * arg.block(i);
            interm = interm << (i * 32);
            result += interm;
        }
        return result;
    }

    UInt &UInt::operator*=(const UInt &arg)
    {
        *this = *this * arg;
        return *this;
    }

    // static
    UInt UInt::pow(const UInt &base, uint32_t exp)
    {
        // build 2 powers of base based on the bits of exp
        std::vector<UInt> powers(32);
        UInt base_power = base;
        for (uint8_t bit = 0; bit < lastBit(exp); ++bit) {
            powers[bit] = base_power;
            base_power *= base_power;
        }
        // now compute the power
        UInt result = 1;
        uint32_t bit_value = 0x1;
        for (uint8_t bit = 0; bit < lastBit(exp); ++bit) {
            if (exp & bit_value) {
                result *= powers[bit];
            }
            bit_value <<= 1;
        }
        return result;
    }

    UInt &UInt::raiseToPower(uint32_t exp)
    {
        *this = pow(*this, exp);
        return *this;
    }

    // static
    UInt UInt::power_modulo(const UInt &base, uint32_t exp, const UInt &modulo)
    {
        // same as power, but modulo on each step
        std::vector<UInt> powers(32);
        UInt base_power = base;
        for (uint8_t bit = 0; bit < lastBit(exp); ++bit) {
            powers[bit] = base_power;
            base_power *= base_power;
            base_power %= modulo;
        }
        UInt result = 1;
        uint32_t bit_value = 0x1;
        for (uint8_t bit = 0; bit < lastBit(exp); ++bit) {
            if (exp & bit_value) {
                result *= powers[bit];
                result %= modulo;
            }
            bit_value <<= 1;
        }
        return result;
    }
    UInt &UInt::raiseToPower(uint32_t exp, const UInt &modulo)
    {
        *this = power_modulo(*this, exp, modulo);
        return *this;
    }

    void UInt::sqrt(UInt &result, uint32_t steps_limit) const
    {
        // case of no limit
        if (steps_limit < 0) {
            steps_limit = INT32_MAX;
        }
        // give a good guess if needed
        if (result == UInt(0)) {
            uint32_t len = this->bits() >> 2;
            result = UInt(1) << len;
        }
        // to find the sqrt(S)=lim(x->inf): X_(n+1) = (Xn + S/Xn)/2
        UInt tmp = UInt(0);
        UInt &old_res = tmp;
        for (uint32_t i = 0; (i < steps_limit) && (old_res != result); i++) {
            old_res = result;
            result += ((*this) / result);
            result /= 2; // todo: implement >> and make this line ">> 1"
        }
        return;
    }
    UInt UInt::sqrt() const
    {
        UInt result = *this;
        this->sqrt(result);
        return result;
    }
    UInt UInt::operator<<(uint32_t offset) const
    {
        UInt result(*this);
        uint32_t zero_blocks = offset / 32u;
        uint32_t reminder = static_cast<int>(offset % 32u);
        uint32_t reminder_comp = (32u - reminder);
        uint32_t carry = 0;
        for (auto i = result._values.begin(); i != result._values.end(); ++i) {
            uint64_t val = static_cast<uint64_t>(*i);
            uint32_t next_value = static_cast<uint32_t>((val << reminder) | carry);
            carry = (val >> reminder_comp);
            *i = next_value;
        }
        if (carry) {
            result._values.push_back(carry);
        }

        for (size_t i = 0; i < zero_blocks; ++i) {
            result._values.insert(result._values.cbegin(), 0);
        }

        return result;
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

    UInt UInt::operator/(uint32_t other) const { return *this / UInt(other); }

    UInt &UInt::operator/=(uint32_t other)
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
            size_t r_len = r.bits();
            size_t b_len = b.bits();
            if (r_len <= b_len + 1) {
                break;
            }
            size_t zeros = r_len - b_len - 1;
            q += base2Cache.get(zeros);
            to_sub = b << zeros;
            r -= to_sub;
        }
        while (r >= b) {
            q += 1;
            r -= b;
        }
    }

    bool UInt::operator<(const UInt &other) const { return compare(*this, other) < 0; }
    bool UInt::operator<=(const UInt &other) const { return compare(*this, other) <= 0; }
    bool UInt::operator>(const UInt &other) const { return compare(*this, other) > 0; }
    bool UInt::operator>=(const UInt &other) const { return compare(*this, other) >= 0; }
    // static
    int8_t UInt::compare(const UInt &a, const UInt &b)
    {
        if (a.size() < b.size())
            return -1;
        if (a.size() > b.size())
            return 1;
        if (lastBit(a.lastBlock()) < lastBit(b.lastBlock()))
            return -1;
        if (lastBit(a.lastBlock()) > lastBit(b.lastBlock()))
            return 1;
        auto ia = a._values.rbegin();
        auto ib = b._values.rbegin();
        for (; ia != a._values.rend() && ib != b._values.rend(); ia++, ib++) {
            if (*ia != *ib) {
                if (*ia < *ib)
                    return -1;
                if (*ia > *ib)
                    return 1;
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
    uint32_t UInt::block(int i) const { return _values[i]; }
    uint32_t UInt::lastBlock() const { return _values[size() - 1]; }

    UInt UInt::negate() const
    {
        UInt result;
        for (uint32_t _value : _values) {
            result._values.push_back(~_value);
        }
        // trim leading zeroes
        while (result.size() && result._values[result._values.size() - 1] == 0) {
            result._values.pop_back();
        }
        return result;
    }

    size_t UInt::bits() const { return (size() - 1) * 32 + lastBit(lastBlock()); }

} // namespace large_numbers