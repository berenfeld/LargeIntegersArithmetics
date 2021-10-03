#pragma once

#include <string>
#include <vector>
#include "uint.h"

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
}