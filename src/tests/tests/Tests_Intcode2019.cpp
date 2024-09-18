
#include <iostream>

#include "runtime/Program.hpp"

#define LAUNCH_TEST(YEAR, DAY, PART) \
std::cout << #YEAR"-"#DAY"-P"#PART" -> "; \
if (aoc::runtime::Program::Launch({ argv[0], "-y", #YEAR, "-d", #DAY, "-p"#PART }) == 0) \
{ \
    std::cout << "OK" << std::endl; \
} \
else \
{ \
    std::cout << "CRITICAL ERROR" << std::endl; \
    return -1; \
} \

int main(int argc, char* argv[])
{
    LAUNCH_TEST(2019, 2, 1);
    LAUNCH_TEST(2019, 2, 2);
    LAUNCH_TEST(2019, 5, 1);
    LAUNCH_TEST(2019, 5, 2);
}
