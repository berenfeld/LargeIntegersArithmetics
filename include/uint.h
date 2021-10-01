#include <string>
#include <vector>

namespace large_numbers
{
    class UInt
    {
    public:
        UInt(const std::string& str, int base = 10);

        std::string toString(int base = 10) const;
    private:
        std::vector<uint32_t> _values;
    };
}