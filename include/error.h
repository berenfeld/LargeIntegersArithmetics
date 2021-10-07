#include <stdexcept>

namespace large_numbers
{
class Error : public std::runtime_error
{
  public:
    Error(const std::string &msg) : std::runtime_error(msg) {}
};
} // namespace large_numbers