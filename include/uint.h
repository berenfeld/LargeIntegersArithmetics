#pragma once

#include "consts.h"
#include <functional>
#include <string>
#include <vector>

namespace large_numbers
{
    class UInt
    {
      public:
        UInt();
        UInt(LN_BLOCK_TYPE value);
        UInt(const std::string &str, int base = 0);

        // comparison
        bool operator==(const UInt &other) const;
        bool operator==(LN_BLOCK_TYPE value) const;
        bool operator!=(const UInt &other) const;
        bool operator!=(LN_BLOCK_TYPE value) const;

        // addition
        UInt &operator+=(const UInt &other);
        UInt operator+(const UInt &other) const;
        UInt &operator+=(LN_BLOCK_TYPE arg);
        UInt operator+(LN_BLOCK_TYPE arg);

        // subsctraction
        UInt &operator-=(const UInt &other);
        UInt operator-(const UInt &other) const;
        UInt &operator-=(LN_BLOCK_TYPE arg);
        UInt operator-(LN_BLOCK_TYPE arg);

        // multiplication
        UInt operator*(LN_BLOCK_TYPE arg) const;
        UInt &operator*=(LN_BLOCK_TYPE arg);
        /**
         * @brief Multiply this UNit by arg, adding the result to the result argument
         * starting with block add_to_block
         *
         * @param arg
         * @param result
         * @param add_to_block
         * @return UInt&
         */
        void mulAdd(LN_BLOCK_TYPE arg, UInt &result, size_t add_to_block) const;
        UInt operator*(const UInt &arg) const;
        UInt &operator*=(const UInt &arg);

        // power
        static UInt pow(const UInt &base, LN_BLOCK_TYPE exp);
        UInt &raiseToPower(LN_BLOCK_TYPE exp);

        // shift
        UInt operator<<(LN_BLOCK_TYPE offset) const;

        // division
        UInt operator/(const UInt &other) const;
        UInt &operator/=(const UInt &other);
        UInt operator/(LN_BLOCK_TYPE other) const;
        UInt &operator/=(LN_BLOCK_TYPE other);
        UInt operator%(const UInt &other) const;
        UInt &operator%=(const UInt &other);
        static void div_mod(const UInt &a, const UInt &b, UInt &q, UInt &r);

        // power modulo
        static UInt power_modulo(const UInt &base, LN_BLOCK_TYPE exp, const UInt &modulo);
        UInt &raiseToPower(LN_BLOCK_TYPE exp, const UInt &modulo);

        // gcd
        static UInt gcd(const UInt &a, const UInt &b);
        UInt gcdWith(const UInt &other) const;

        // root square
        /**
         * @brief calculate the sqrt of this and put the answer in reference
         * result
         *
         * @param result input - best guess of the sqrt (preferred UInt(0), so
         * the function will guess it by itself). output - the result.
         * @param steps_limit - maximum steps of the sqrt guessing. complexity
         * of this method is O(steps_limit*O(operator/)) = O(steps_limit*n)
         * steps_limit=0 returns initial guess of sqrt (2^(n/2)) steps_limit<0
         * no limit.
         */
        void sqrt(UInt &result, LN_BLOCK_TYPE steps_limit = -1) const;
        /**
         * @brief calculate the sqrt of this and returns it
         */
        UInt sqrt() const;

        // comparison
        bool operator<(const UInt &other) const;
        bool operator<=(const UInt &other) const;
        bool operator>(const UInt &other) const;
        bool operator>=(const UInt &other) const;
        static int8_t compare(const UInt &a, const UInt &b);

        size_t size() const;
        LN_BLOCK_TYPE block(int i) const;
        LN_BLOCK_TYPE lastBlock() const;
        size_t bits() const;
        std::string toString(int base = 10) const;

        friend std::ostream &operator<<(std::ostream &os, const UInt &value) { return os << value.toString(10); }

        class UIntHash
        {
          public:
            size_t operator()(const UInt &key) const
            {
                size_t result = 0;
                for (const LN_BLOCK_TYPE &value : key._values) {
                    result += std::hash<LN_BLOCK_TYPE>()(value);
                }
                return result;
            }
        };

      private:
        /**
         * @brief negate all the bits in the number, and after negation trim
         * leading zeros note : unlike fixed size ~ operator this operator does
         * not reverse. i.e sometimes negate(negate(x)) != x
         * TODO : formalize it, using either fixed block size argument or
         * storing of "negate back" block size
         * @return UInt
         */
        [[nodiscard]] UInt negate() const;

        std::vector<LN_BLOCK_TYPE> _values;
    };

} // namespace large_numbers