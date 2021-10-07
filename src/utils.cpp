#include "utils.h"
#include "base10_cache.h"
#include "consts.h"
#include "error.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>

namespace large_numbers
{
    UInt parseBase10StringValues(const std::string &str)
    {
        base10_cache::initCache();

        std::string str_copy = str;
        UInt result;
        int digit_pos = 0;
        const size_t len = str.size();
        while (digit_pos != len)
        {
            char digit = str_copy.at(len - digit_pos - 1);
            uint32_t digit_value = static_cast<int>(digit - '0');
            result += base10_cache::getUint(digit_pos, digit_value);
            ++digit_pos;
        }
        return result;
    }

    void parseBase16StringValues(const std::string &str,
                                 std::vector<uint32_t> &values)
    {
        std::string left = str;
        uint32_t value;
        const size_t DWORD_HEX_STRING_LEN = 8;
        // remove prefix 0x or 0X
        if ((left.rfind("0x", 0) == 0) || (left.rfind("0X", 0) == 0))
        {
            left = left.substr(2, left.size() - 2);
        }
        do
        {
            const size_t len = left.size();
            if (len == 0)
            {
                break;
            }
            const size_t token_length = std::min(DWORD_HEX_STRING_LEN, len);
            const std::string token = left.substr(len - token_length, token_length);
            left = left.substr(0, len - token_length);
            std::stringstream ss;
            ss << std::hex << token;
            ss >> value;
            values.push_back(value);
        } while (true);
    }

    std::string base16StringOf(const UInt &value, const std::string &prefix)
    {
        std::stringstream ss;
        ss << prefix << std::hex;
        for (int i = value.size() - 1; i >= 0; --i)
        {
            if (i != value.size() - 1)
            {
                ss << std::setfill('0') << std::setw(8);
            }
            ss << value.getBlock(i);
        }
        std::string result = ss.str();
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }

    int guessBaseOf(const std::string &str)
    {
        if (str.empty())
        {
            return 10;
        }
        if ((str.rfind("0x", 0) == 0) || (str.rfind("0X", 0) == 0))
        {
            return 16;
        }

        if (std::find_if(str.begin(), str.end(), [](unsigned char c)
                         { return !std::isdigit(c); }) == str.end())
        {
            return 10;
        }
        if (std::find_if(str.begin(), str.end(), [](unsigned char c)
                         { return !std::isxdigit(c); }) == str.end())
        {
            return 16;
        }
        // no idea
        throw Error("Invalid base " + str);
    }

    UInt rand(int blocks)
    {
        UInt result = 0;
        if (blocks == 0)
        {
            blocks = MAX_RAND_UINT_BLOCKS;
        }
        int num_blocks = std::max(::rand() % blocks, 1); // at least one block
        for (auto i = 0; i < num_blocks; ++i)
        {
            result += ::rand();
            if (i != num_blocks - 1)
            {
                result = result << 32;
            }
        }
        return result;
    }
} // namespace large_numbers