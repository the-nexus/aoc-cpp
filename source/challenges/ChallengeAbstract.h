#pragma once

#include <iostream>
#include <string>
#include <vector>

class ChallengeAbstract
{
public:
    virtual void SetUp(std::vector<std::string> const& inputLines) = 0;
    virtual void Run_PartOne() = 0;
    virtual void Run_PartTwo() = 0;
    virtual void CleanUp() = 0;
};
