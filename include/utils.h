#pragma once

#include "consts.h"
#include "uint.h"
#include <string>
#include <vector>

namespace large_numbers
{
    /**
     * @brief Remove whitespaces from beginning and end of a string, in-place
     *
     * @param s
     */
    void trim(std::string &s);

    /**
     * @brief parse a base 10 string to uint32_t numbers
     *
     * @param str
     * @param values
     */
    UInt parseBase10StringValues(const std::string &str);

    /**
     * @brief parse a base 16 string to uint32_t numbers
     *
     * @param str
     * @param values
     */
    void parseBase16StringValues(const std::string &str, std::vector<uint32_t> &values);

    /**
     * @brief Format a base16 string of the given value
     *
     * @param value
     * @param prefix
     * @return std::string
     */
    std::string base16StringOf(const UInt &value, const std::string &prefix = "0X");

    /**
     * @brief Return a bse 10 representation of the given value
     *
     * @param value
     * @return std::string
     */
    std::string base10StringOf(const UInt &value);

    /**
     * @brief Try to make an educated guess for the base of str
     * The guess is natural. if the string starts with 0x or 0X its base 16,
     * else if its only digits its base 10, else if its only hexadecimal its base
     * 16,
     *
     * @param str
     * @return int
     */
    int guessBaseOf(const std::string &str);

    /**
     * @brief Generate a random number with the given number of blocks
     * if blocks is 0, MAX_RAND_UINT_BLOCKS are used
     * @param blocks
     * @return UInt
     */
    UInt rand(int blocks = 0);

    std::string executeCommand(const std::string &command, int &return_code);

    /**
     * @brief Returns the place of the most significant bit in the
     * binary representation of n
     *
     * @param n
     * @return uint8_t
     */
    uint8_t lastBit(uint32_t n);

    bool isPrime(uint32_t n);

} // namespace large_numbers