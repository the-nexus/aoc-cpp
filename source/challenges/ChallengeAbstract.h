#pragma once

#include <iostream>
#include <string>
#include <vector>

class ChallengeAbstract
{
public:
    virtual void SetUp(std::vector<std::string> const& inputLines) {};
    virtual void Run_PartOne() { std::cout << "WARNING: Part One Not Implemented" << std::endl; }
    virtual void Run_PartTwo() { std::cout << "WARNING: Part Two Not Implemented" << std::endl; }
    virtual void CleanUp() {};
};
