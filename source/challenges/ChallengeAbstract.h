#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class ChallengeAbstract
{
public:
    ChallengeAbstract(std::shared_ptr<std::vector<std::string>> const& inputLines) : m_inputLines(inputLines) {}
    virtual ~ChallengeAbstract() {}

    virtual void SetUp(std::vector<std::string> const& inputLines) {};
    virtual void Run_PartOne() { std::cout << "WARNING: Part One Not Implemented" << std::endl; }
    virtual void Run_PartTwo() { std::cout << "WARNING: Part Two Not Implemented" << std::endl; }
    virtual void CleanUp() {};

private:
    std::shared_ptr<std::vector<std::string>> m_inputLines;
};
