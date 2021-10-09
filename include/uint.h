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

        // multiplication
        UInt operator*(uint32_t arg) const;

        // shift
        UInt operator<<(uint32_t offset) const;

        // division
        UInt operator/(const UInt &other) const;
        UInt operator/=(const UInt &other);
        UInt operator%(const UInt &other) const;
        static void div_mod(const UInt &a, const UInt &b, UInt &q, UInt &r);

        // comparison
        bool operator<(const UInt &other) const;
        bool operator<=(const UInt &other) const;
        bool operator>(const UInt &other) const;
        bool operator>=(const UInt &other) const;
        static int8_t compare(const UInt &a, const UInt &b);

        [[nodiscard]] size_t size() const;
        uint32_t block(int i) const;
        uint32_t lastBlock() const;
        size_t bits() const;

        [[nodiscard]] std::string toString(int base = 10) const;

        friend std::ostream &operator<<(std::ostream &os, const UInt &value) { return os << value.toString(16); }

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