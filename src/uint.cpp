#include "uint.h"
#include "error.h"
#include "utils.h"
#include <sstream>
#include <algorithm>

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
            case 2: throw Error("Base not supported"); break;
            case 10: throw Error("Base not supported"); break;
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

    UInt UInt::operator *(uint32_t arg) const
    {
        UInt result;
        for (const uint32_t& value : _values)
        {
            // TODO: handle overflow
            result._values.push_back(arg * value);
        }
        return result;
    }

    std::string UInt::toString(int base) const
    {
        switch(base)
        {
            case 2: throw Error("Base not supported"); break;
            case 10: throw Error("Base not supported"); break;
            case 16: {
                std::stringstream ss;
                for (const uint32_t& value : _values) {
                    ss << std::hex << value;
                }
                std::string result = ss.str();
                std::transform(result.begin(), result.end(),result.begin(), ::toupper);
                return result;
            }
            default: throw Error("Base not supported");
        }
        
    }
}