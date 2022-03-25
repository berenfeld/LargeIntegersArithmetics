#include <stdexcept>
#include <string>

#ifndef LN_ASSERT
#ifdef NDEBUG
#define LN_ASSERT(cond, message)
#else
#define LN_ASSERT(cond, message)                                                                                       \
    do {                                                                                                               \
        if (!(cond)) {                                                                                                 \
            throw Error(message);                                                                                      \
        }                                                                                                              \
    } while (0)
#endif
#endif

namespace large_numbers
{
    class Error : public std::runtime_error
    {
      public:
        Error(const std::string &msg);
    };
} // namespace large_numbers
