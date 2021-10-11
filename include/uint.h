#pragma once

#include <functional>
#include <string>
#include <vector>

namespace large_numbers
{
    class UInt
    {
      public:
        UInt();
        UInt(uint32_t value);
        UInt(const std::string &str, int base = 0);

        // comparison
        bool operator==(const UInt &other) const;
        bool operator==(uint32_t value) const;
        bool operator!=(const UInt &other) const;
        bool operator!=(uint32_t value) const;

        // addition
        UInt &operator+=(const UInt &other);
        UInt operator+(const UInt &other) const;
        UInt &operator+=(uint32_t arg);
        UInt operator+(uint32_t arg);

        // subsctraction
        UInt &operator-=(const UInt &other);
        UInt operator-(const UInt &other) const;
        UInt &operator-=(uint32_t arg);
        UInt operator-(uint32_t arg);

        // multiplication
        UInt operator*(uint32_t arg) const;
        UInt &operator*=(uint32_t arg);
        UInt operator*(const UInt &arg) const;
        UInt &operator*=(const UInt &arg);

        // power
        static UInt pow(const UInt &base, uint32_t exp);
        UInt &raiseToPower(uint32_t exp);

        // shift
        UInt operator<<(uint32_t offset) const;

        // division
        UInt operator/(const UInt &other) const;
        UInt &operator/=(const UInt &other);
        UInt operator/(uint32_t other) const;
        UInt &operator/=(uint32_t other);
        UInt operator%(const UInt &other) const;
        UInt &operator%=(const UInt &other);
        static void div_mod(const UInt &a, const UInt &b, UInt &q, UInt &r);

        // power modulo
        static UInt power_modulo(const UInt &base, uint32_t exp, const UInt &modulo);
        UInt &raiseToPower(uint32_t exp, const UInt &modulo);

        // root square
        /**
         * @brief calculate the sqrt of this and put the answer in reference result
         *
         * @param result input - best guess of the sqrt (preferred UInt(0), so the function will guess it by itself).
         *               output - the result.
         * @param steps_limit - maximum steps of the sqrt guessing. complexity of this method is
         * O(steps_limit*O(operator/)) = O(steps_limit*n) steps_limit=0 returns initial guess of sqrt (2^(n/2))
         *                      steps_limit<0 no limit.
         */
        void sqrt(UInt &result, uint32_t steps_limit = -1) const;
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
        uint32_t block(int i) const;
        uint32_t lastBlock() const;
        size_t bits() const;
        std::string toString(int base = 10) const;

        friend std::ostream &operator<<(std::ostream &os, const UInt &value) { return os << value.toString(); }

        class UIntHash
        {
          public:
            size_t operator()(const UInt &key) const
            {
                size_t result = 0;
                for (const uint32_t &value : key._values) {
                    result += std::hash<uint32_t>()(value);
                }
                return result;
            }
        };

      private:
        /**
         * @brief negate all the bits in the number, and after negation trim leading
         * zeros note : unlike fixed size ~ operator this operator does not reverse.
         * i.e sometimes negate(negate(x)) != x
         * TODO : formalize it, using either fixed block size argument or storing of
         * "negate back" block size
         * @return UInt
         */
        [[nodiscard]] UInt negate() const;

        std::vector<uint32_t> _values;
    };

} // namespace large_numbers