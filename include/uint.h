#pragma once

#include <string>
#include <vector>
#include <functional>

namespace large_numbers
{
    class UInt
    {
    public:
        UInt();
        UInt(uint32_t value);
        UInt(const std::string& str, int base = 10);

        bool operator ==(const UInt& other) const;
        UInt& operator +=(const UInt& other);

        UInt operator *(uint32_t arg) const;

        std::string toString(int base = 10) const;

        class UIntHash
        {
            public:
            size_t operator()(const UInt& key) const
            {
                size_t result = 0;
                for (const uint32_t& value : key._values)
                {
                    result += std::hash<uint32_t>()(value);
                }
                return result;
            }
        };
    private:
        std::vector<uint32_t> _values;
    };


}