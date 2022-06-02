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

        // increment/decrement
        UInt &operator++();
        UInt &operator--();
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
        static UInt pow(const UInt &base, const UInt &exp);
        UInt &raiseToPower(const UInt &exp);

        // shift
        UInt operator<<(size_t offset) const;
        UInt &operator<<=(size_t offset);
        UInt operator>>(size_t offset) const;
        UInt &operator>>=(size_t offset);

        // division
        UInt operator/(const UInt &other) const;
        UInt &operator/=(const UInt &other);
        UInt operator/(LN_BLOCK_TYPE other) const;
        UInt &operator/=(LN_BLOCK_TYPE other);
        UInt operator%(const UInt &other) const;
        UInt &operator%=(const UInt &other);
        static void div_mod(const UInt &a, const UInt &b, UInt &q, UInt &r);

        // binary
        UInt operator&(const UInt &other) const;
        UInt &operator&=(const UInt &other);

        // power modulo
        static UInt powerModulo(const UInt &base, const UInt &exp, const UInt &modulo);
        UInt &raiseToPower(const UInt &exp, const UInt &modulo);

        // gcd
        static UInt gcd(const UInt &a, const UInt &b);
        UInt gcdWith(const UInt &other) const;

        // lcm
        static UInt lcm(const UInt &a, const UInt &b);
        UInt lcmWith(const UInt &other) const;

        // root square
        static UInt sqrt(const UInt &n);
        UInt sqrt() const;

        // comparison
        bool operator<(const UInt &other) const;
        bool operator<=(const UInt &other) const;
        bool operator>(const UInt &other) const;
        bool operator>=(const UInt &other) const;
        static int8_t compare(const UInt &a, const UInt &b);

        size_t size() const;
        const LN_BLOCK_TYPE &block(int i) const;
        const LN_BLOCK_TYPE &lastBlock() const;
        size_t bits() const;
        LN_BLOCK_TYPE bit(size_t i) const;
        std::string toString(int base = 10) const;

        friend std::ostream &operator<<(std::ostream &os, const UInt &value) { return os << value.toString(10); }
        friend class UIntHasher;

      private:
        /**
         * @brief negate all the bits in the number, and after negation trim
         * leading zeros note : unlike fixed size ~ operator this operator does
         * not reverse. i.e sometimes negate(negate(x)) != x
         * TODO : formalize it, using either fixed block size argument or
         * storing of "negate back" block size
         * @return UInt
         */
        UInt negate() const;

        /**
         * @brief Remove trailing zeros from the _values
         *
         */
        void trimZeros();

        std::vector<LN_BLOCK_TYPE> _values;
    };

    class UIntHasher
    {
      public:
        std::size_t operator()(const UInt &element) const;
    };
}; // namespace large_numbers
