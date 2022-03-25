#include "cerror.h"
#include <string>

namespace large_numbers
{
    Error::Error(const std::string &msg) : std::runtime_error(msg) {}
} // namespace large_numbers