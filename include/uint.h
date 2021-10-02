#include <string>
#include <vector>

namespace large_numbers
{
    class UInt
    {
    public:
        UInt();
        UInt(uint32_t value);
        UInt(const std::string& str, int base = 10);

        bool operator ==(const UInt& other) const;

        UInt operator *(uint32_t arg) const;

        std::string toString(int base = 10) const;
    private:
        std::vector<uint32_t> _values;
    };
}