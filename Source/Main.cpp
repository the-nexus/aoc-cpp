
#include <Challenges/Factory.hpp>

int main(int argc, char* argv[])
{
    int const year = 2020;
    int const day = 11;
    bool const shouldRunPartOne = true;
    bool const shouldRunPartTwo = true;

    std::vector<std::string> inputLines;
    // Read file op

    AOC::Challenges::Factory::RegisterAllChallenges();
    auto challenge = AOC::Challenges::Factory::Produce({year, day}, std::move(inputLines));
    if (!challenge)
    {
        return -1;
    }

    if (shouldRunPartOne) challenge->RunPartOne();
    if (shouldRunPartTwo) challenge->RunPartTwo();
}