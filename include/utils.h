#pragma once

#include <string>
#include <vector>
#include "uint.h"
#include "consts.h"

namespace large_numbers
{
     /**
     * @brief parse a base 10 string to uint32_t numbers
     * 
     * @param str 
     * @param values 
     */
    UInt parseBase10StringValues(const std::string& str);

    /**
     * @brief parse a base 16 string to uint32_t numbers
     * 
     * @param str 
     * @param values 
     */
    void parseBase16StringValues(const std::string& str, std::vector<uint32_t>& values);

    /**
     * @brief Format a base16 string of the given value
     * 
     * @param value 
     * @param prefix 
     * @return std::string 
     */
    std::string base16StringOf(const UInt& value, const std::string& prefix = "0X");

    /**
     * @brief Try to make an educated guess for the base of str
     * The guess is natural. if the string starts with 0x or 0X its base 16,
     * else if its only digits its base 10, else if its only hexadecimal its base 16,
     *
     * @param str 
     * @return int 
     */
    int guessBaseOf(const std::string& str);
}