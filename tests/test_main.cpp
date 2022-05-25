#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

int main(int argc, char **argv)
{
    spdlog::set_pattern("%H:%M:%S.%f %l %v");
    spdlog::info("Starting tests...");
    ::testing::InitGoogleTest(&argc, argv);
    const int result = RUN_ALL_TESTS();
    spdlog::info("tests Done... result is {}", result);
    return result;
}