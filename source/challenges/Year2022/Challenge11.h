#pragma once

#include "../ChallengeAbstract.h"
#include "../tools/StringTool.h"
#include <deque>
#include <algorithm>

namespace Year2022
{
    class Challenge11 final : public ChallengeAbstract
    {
        typedef unsigned long long worry_t;

        struct MonkeyData
        {
            std::vector<worry_t> m_items;
            worry_t m_operationLhs = 0;
            worry_t m_operationRhs = 0;
            char m_operationType = '+';
            worry_t m_testDivider = 1;
            int m_testSuccessIndex = 0;
            int m_testFailureIndex = 0;
        };

        struct MonkeyRuntimeData
        {
            std::deque<worry_t> m_items;
            worry_t m_itemInspectCount = 0;
        };

        std::vector<MonkeyData> m_monkeys;
        worry_t m_smallestCommonMultiple = 1;

    public:
        Challenge11(std::vector<std::string> const& inputLines)
        {
            std::vector<std::string> lineArgs;

            for (size_t lineIndex = 0; lineIndex < inputLines.size(); lineIndex += 7)
            {
                MonkeyData& monkey = m_monkeys.emplace_back();

                // Starting items
                StringTool::SplitString(inputLines[lineIndex + 1].substr(18), ", ", lineArgs);
                monkey.m_items.resize(lineArgs.size());
                for (size_t argIndex = 0; argIndex < lineArgs.size(); ++argIndex)
                {
                    monkey.m_items[argIndex] = atoi(lineArgs[argIndex].c_str());
                }
                lineArgs.clear();

                // Operation
                StringTool::SplitString(inputLines[lineIndex + 2].substr(19), " ", lineArgs);
                monkey.m_operationLhs = lineArgs[0][0] == 'o' ? 0 : atoi(lineArgs[0].c_str());
                monkey.m_operationRhs = lineArgs[2][0] == 'o' ? 0 : atoi(lineArgs[2].c_str());
                monkey.m_operationType = lineArgs[1][0];
                lineArgs.clear();

                // Test
                monkey.m_testDivider = atoi(inputLines[lineIndex + 3].substr(21).c_str());
                monkey.m_testSuccessIndex = atoi(inputLines[lineIndex + 4].substr(29).c_str());
                monkey.m_testFailureIndex = atoi(inputLines[lineIndex + 5].substr(30).c_str());

                m_smallestCommonMultiple *= monkey.m_testDivider;
            }
        }

        virtual void Run_PartOne() override
        {
            std::cout << SimulateMonkeyBusiness(20, true) << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::cout << SimulateMonkeyBusiness(10000, false) << std::endl;
        }

    private:
        worry_t SimulateMonkeyBusiness(int const roundCount, bool const doesItemWorryReduce) const
        {
            std::vector<MonkeyRuntimeData> runtimeMonkeys;
            runtimeMonkeys.resize(m_monkeys.size());
            for (size_t monkeyIndex = 0; monkeyIndex < m_monkeys.size(); ++monkeyIndex)
            {
                runtimeMonkeys[monkeyIndex].m_items.assign(m_monkeys[monkeyIndex].m_items.begin(), m_monkeys[monkeyIndex].m_items.end());
            }

            for (int roundNumber = 0; roundNumber < roundCount; ++roundNumber)
            {
                for (size_t monkeyIndex = 0; monkeyIndex < m_monkeys.size(); ++monkeyIndex)
                {
                    MonkeyData const& monkeyData = m_monkeys[monkeyIndex];
                    MonkeyRuntimeData& runtimeMonkey = runtimeMonkeys[monkeyIndex];

                    while (runtimeMonkey.m_items.size() > 0)
                    {
                        worry_t item = runtimeMonkey.m_items.front();
                        runtimeMonkey.m_items.pop_front();
                        ++runtimeMonkey.m_itemInspectCount;

                        worry_t const opLhs = monkeyData.m_operationLhs == 0 ? item : monkeyData.m_operationLhs;
                        worry_t const opRhs = monkeyData.m_operationRhs == 0 ? item : monkeyData.m_operationRhs;
                        if (monkeyData.m_operationType == '+')
                        {
                            item = opLhs + opRhs;
                        }
                        else if (monkeyData.m_operationType == '*')
                        {
                            item = opLhs * opRhs;
                        }
                        else
                        {
                            std::cout << "UNSUPPORTED OP " << monkeyData.m_operationType << std::endl;
                        }

                        if (doesItemWorryReduce)
                        {
                            item /= 3;
                        }

                        item %= m_smallestCommonMultiple;

                        worry_t const testResultIndex = item % monkeyData.m_testDivider == 0 ? monkeyData.m_testSuccessIndex : monkeyData.m_testFailureIndex;
                        runtimeMonkeys[testResultIndex].m_items.push_back(item);
                    }
                }
            }

            std::sort(runtimeMonkeys.begin(), runtimeMonkeys.end(), [](MonkeyRuntimeData const& lhs, MonkeyRuntimeData const& rhs) -> bool {
                return lhs.m_itemInspectCount > rhs.m_itemInspectCount;
            });

            return runtimeMonkeys[0].m_itemInspectCount * runtimeMonkeys[1].m_itemInspectCount;
        }
    };
}
