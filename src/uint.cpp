#include "uint.h"
#include "error.h"
#include "utils.h"
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <iostream>

namespace large_numbers
{
    UInt::UInt()
    {}

    UInt::UInt(uint32_t value)
    {
        _values.push_back(value);
    }

    UInt::UInt(const std::string& str, int base)
    {
        switch(base)
        {
            case 10: {
                UInt result = parseBase10StringValues(str);
                _values = result._values;
                break;
            }
            case 16: {
                parseBase16StringValues(str, _values);
                break;
            }
            default: throw Error("Base not supported");
        }
        
    }

    bool UInt::operator ==(const UInt& other) const
    {
        return _values == other._values;
    }

    UInt& UInt::operator +=(const UInt& other)
    {
        _values.resize(std::max(_values.size(), other._values.size()));
        uint32_t add_to_next_value = 0;
        for(int i=0; i<other._values.size(); ++i)
        {
            uint64_t added_value = static_cast<uint64_t>(_values[i]) + static_cast<uint64_t>(other._values[i]) + add_to_next_value;
            _values[i] = added_value;
            add_to_next_value = added_value >> 32;
        }
        if (add_to_next_value) {
            _values.push_back(add_to_next_value);
        }
        return *this;
    }

    UInt UInt::operator *(uint32_t arg) const
    {
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

    std::string UInt::toString(int base) const
    {
        switch(base)
        {
            case 16: {
                std::stringstream ss;
                for (int i=_values.size()-1;i>=0;--i) {
                    ss << std::hex;
                    if (i != _values.size() - 1) {
                        ss << std::setfill('0') << std::setw(8);
                    }  
                    ss << _values[i];
                }
                std::string result = ss.str();
                std::transform(result.begin(), result.end(),result.begin(), ::toupper);
                return result;
            }
            default: throw Error("Base not supported");
        }
        
    }
}