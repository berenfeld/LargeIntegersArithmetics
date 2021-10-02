#include "utils.h"
#include <sstream>

namespace large_numbers
{
    /**
     * @brief parse a base 16 string to uint32_t numbers
     * 
     * @param str 
     * @param values 
     */
    void parseBase16StringValues(const std::string& str, std::vector<uint32_t>& values)
    {
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
            ss << std::hex << token;
            ss >> value;
            values.push_back(value);
        } while(true);
    }
}