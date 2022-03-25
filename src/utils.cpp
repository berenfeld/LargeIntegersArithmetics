#include "utils.h"
#include "base10_cache.h"
#include "cerror.h"
#include "consts.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>

namespace large_numbers
{
    void ltrim(std::string &s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    }

    void rtrim(std::string &s)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
    }

    void trim(std::string &s)
    {
        ltrim(s);
        rtrim(s);
    }

    UInt parseBase10StringValues(const std::string &str)
    {
        std::string str_copy = str;
        UInt result = 0;
        size_t digit_pos = 0;
        const size_t len = str.size();
        while (digit_pos != len) {
            char digit = str_copy.at(len - digit_pos - 1);
            uint32_t digit_value = static_cast<int>(digit - '0');
            result += base10Cache.get(digit_pos, digit_value);
            ++digit_pos;
        }
        return result;
    }

    void parseBase16StringValues(const std::string &str, std::vector<LN_BLOCK_TYPE> &values)
    {
        std::string left = str;
        trim(left);
        LN_BLOCK_TYPE value;
        // remove prefix 0x or 0X
        if ((left.rfind("0x", 0) == 0) || (left.rfind("0X", 0) == 0)) {
            left = left.substr(2, left.size() - 2);
        }
        do {
            const size_t len = left.size();
            if (len == 0) {
                break;
            }
            const size_t token_length = std::min(LN_HEX_DIGITS_IN_BLOCK, len);
            const std::string token = left.substr(len - token_length, token_length);
            left = left.substr(0, len - token_length);
            std::stringstream ss;
            ss << std::hex << token;
            ss >> value;
            values.push_back(value);
        } while (true);
    }

    std::string base10StringOf(const UInt &value)
    {
        if (value == UInt(0)) {
            return "0";
        }
        std::stringstream ss;

        const UInt UINT_10 = UInt(10);
        UInt num = value;
        UInt q, r;
        while (num != 0) {
            UInt::div_mod(num, UINT_10, q, r);
            num = q;
            ss << static_cast<char>('0' + r.block(0));
        }
        std::string result = ss.str();
        std::reverse(result.begin(), result.end());
        return result;
    }

    std::string base16StringOf(const UInt &value, const std::string &prefix)
    {
        if (value.size() == 0) {
            return "0X0";
        }
        std::stringstream ss;
        ss << prefix << std::hex;
        for (int i = value.size() - 1; i >= 0; --i) {
            if (static_cast<size_t>(i) != value.size() - 1) {
                ss << std::setfill('0') << std::setw(LN_HEX_DIGITS_IN_BLOCK);
            }
            ss << value.block(i);
        }
        std::string result = ss.str();
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }

    int guessBaseOf(const std::string &str)
    {
        if (str.empty()) {
            return 10;
        }
        if ((str.rfind("0x", 0) == 0) || (str.rfind("0X", 0) == 0)) {
            return 16;
        }

        if (std::find_if(str.begin(), str.end(), [](unsigned char c) { return !std::isdigit(c); }) == str.end()) {
            return 10;
        }
        if (std::find_if(str.begin(), str.end(), [](unsigned char c) { return !std::isxdigit(c); }) == str.end()) {
            return 16;
        }
        // no idea
        throw Error("Invalid base " + str);
    }

    UInt rand(int blocks)
    {
        UInt result = 0;
        if (blocks == 0) {
            blocks = LN_MAX_RAND_UINT_BLOCKS;
        }
        int num_blocks = std::max(::rand() % blocks, 1); // at least one block
        for (auto i = 0; i < num_blocks; ++i) {
            // random 64 bit unsigned integer
            result += ((static_cast<LN_BLOCK_TYPE>(::rand()) << 32) + ::rand());
            if (i != num_blocks - 1) {
                result = result << LN_BITS_IN_BLOCK;
            }
        }
        return result;
    }

    std::string executeCommand(const std::string &command, int &return_code)
    {
        std::array<char, 128> buffer;
        std::string result;
        FILE *pipe = popen(command.c_str(), "r");
        while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
            result += buffer.data();
        }
        return_code = pclose(pipe);
        return result;
    }

    size_t lastBit(LN_BLOCK_TYPE n) { return n == 0 ? 0 : static_cast<size_t>(log2(n)) + 1; }

    /**
     * @brief basic primility check for small numbers
     * check for divisors from 1 to sqrt(n)
     * return true for 0,1
     * @param n
     * @return true
     * @return false
     */
    bool isPrime(uint32_t n)
    {
        if (n <= 3) {
            return true;
        }
        UInt q, r;
        const uint32_t check_until = static_cast<uint32_t>(std::ceil(std::sqrt(static_cast<float>(n))));
        for (uint32_t num = 2; num <= check_until; ++num) {
            UInt::div_mod(n, num, q, r);
            if (r == 0) {
                return false;
            }
        }
        return true;
    }
} // namespace large_numbers