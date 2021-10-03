#include "utils.h"
#include "base10_cache.h"
#include <sstream>
#include <algorithm>
#include <string>


namespace large_numbers
{
    UInt parseBase10StringValues(const std::string& str)
    {
        base10_cache::initCache();

        std::string str_copy = str;
        UInt result;
        int digit_pos = 0;
        const size_t len = str.size();
        do {
            if (digit_pos == len) {
                break;
            }
            char digit = str_copy.at(len - digit_pos - 1);
            uint32_t digit_value = static_cast<int>(digit - '0');
            result += base10_cache::getUint(digit_pos, digit_value);
            ++digit_pos;
        } while(1);
        return result;
    }

    void parseBase16StringValues(const std::string& str, std::vector<uint32_t>& values)
    {
        std::string left = str;
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
            std::stringstream ss;
            ss << std::hex << token;
            ss >> value;
            values.push_back(value);
        } while(true);
    }

}