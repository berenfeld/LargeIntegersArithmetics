#include "uint.h"
#include "error.h"
#include "utils.h"
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <cmath>

namespace large_numbers {
    UInt::UInt() {}

    UInt::UInt(uint32_t value) {
        _values.push_back(value);
    }

    UInt::UInt(const std::string &str, int base) {
        switch (base) {
            case 10: {
                UInt result = parseBase10StringValues(str);
                _values = result._values;
                break;
            }
            case 16: {
                parseBase16StringValues(str, _values);
                break;
            }
            default:
                throw Error("Base not supported");
        }

    }

    bool UInt::operator==(const UInt &other) const {
        return _values == other._values;
    }

    bool UInt::operator==(uint32_t value) const {
        if (value) {
            return size() == 1 && _values[0] == value;
        } else {
            return _values.empty();
        }
    }

    bool UInt::operator!=(const UInt &other) const {
        return !(*this == other);
    }

    bool UInt::operator!=(uint32_t value) const {
        return !(*this == value);
    }

    UInt &UInt::operator+=(const UInt &other) {        
        const size_t max_block = std::max(size(), other.size());
        _values.resize(max_block);
        uint32_t add_to_next_value = 0;
        int i = 0;        
        while (i < max_block) {
            uint64_t added_value = static_cast<uint64_t>(_values[i]) + static_cast<uint64_t>(add_to_next_value) +
                ( i < other.size() ? static_cast<uint64_t>(other._values[i]) : 0 );
            _values[i] = static_cast<uint32_t>(added_value);
            add_to_next_value = added_value >> 32;
            ++ i;
        }        
        if (add_to_next_value) {
            _values.push_back(add_to_next_value);
        }
        return *this;
    }

    UInt UInt::operator+(const UInt &other) const {
        return UInt(*this) += other;
    }

    UInt& UInt::operator+=(uint32_t arg) {
        *this += UInt(arg);
        return *this;
    }

    UInt UInt::operator+(uint32_t arg) {
        return UInt(*this) + UInt(arg);
    }

    UInt UInt::operator*(uint32_t arg) const {
        UInt result;
        uint32_t add_to_next_value = 0;
        uint64_t arg64 = static_cast<uint64_t>(arg);
        for (const uint32_t& value : _values) {
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

    UInt UInt::operator-(const UInt &other) const {
        return UInt(*this) -= other;
    }

    UInt &UInt::operator-=(const UInt &other) {
        const size_t other_size = other.size();        
        UInt other_negate = other.negate();    
        // negate value of other is 2^n - other - 1, where n is the number of bits of other
        // rounded up to 32. so we need to substract 2^n and add 1 back
        *this += other_negate;        
        *this += 1;        
        for (int i = other_size; i < _values.size(); ++ i)
        {
            if (_values[i] != 0) {
                -- _values[i];
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

    std::string UInt::toString(int base) const {
        switch (base) {
            case 16: {
                std::stringstream ss;
                ss << "0X" << std::hex;
                for (int i = size() - 1; i >= 0; --i) {
                    if (i != size() - 1) {
                        ss << std::setfill('0') << std::setw(8);
                    }
                    ss << _values[i];
                }
                std::string result = ss.str();
                std::transform(result.begin(), result.end(), result.begin(), ::toupper);
                return result;
            }
            default:
                throw Error("Base not supported");
        }
    }

    size_t UInt::size() const {
        return _values.size();
    }

    UInt UInt::negate() const {
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
}