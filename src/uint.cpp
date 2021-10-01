#include "uint.h"
#include "error.h"
#include <sstream>
#include <algorithm>

namespace large_numbers
{
    UInt::UInt(const std::string& str, int base)
    {
        switch(base)
        {
            case 2: throw Error("Base not supported"); break;
            case 10: throw Error("Base not supported"); break;
            case 16: {
                std::string left = str;
                std::stringstream ss;
                uint32_t value;
                const size_t DWORD_HEX_STRING_LEN = 8;
                do
                {
                    const size_t len = left.size();
                    if (len == 0) {
                        break;
                    }
                    const size_t token_length = std::min(DWORD_HEX_STRING_LEN, len);
                    const std::string token = left.substr(len - token_length, token_length);
                    left = left.substr(0, len - token_length);
                    ss << token;
                    ss >> value;
                    _values.push_back(value);
                } while(true);
                break;
            }
            default: throw Error("Base not supported");
        }
        
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
                return ss.str();
            }
            default: throw Error("Base not supported");
        }
        
    }
}