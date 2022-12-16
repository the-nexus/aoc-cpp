#pragma once

#include "../ChallengeAbstract.h"
#include "../tools/StringTool.h"
#include <map>
#include <set>

namespace Year2022
{
    class Challenge16 : public ChallengeAbstract
    {
    private:
        std::map<int, int> m_rates;
        std::map<int, std::vector<int>> m_tunnels;

    public:
        virtual void SetUp(std::vector<std::string> const& inputLines) override
        {
            for (std::string const& inputLine : inputLines)
            {
                size_t const srcLabelIndex = inputLine.find_first_of(' ') + 1;
                size_t const rateStartIndex = inputLine.find_first_of('=', srcLabelIndex) + 1;
                size_t const rateEndIndex = inputLine.find_first_of(';', rateStartIndex);
                size_t const dstLabelsIndex = inputLine.find_first_of(' ', inputLine.find_last_of("valve")) + 1;

                //std::cout << inputLine.substr(srcLabelIndex, 2) << "|" << inputLine.substr(rateStartIndex, rateEndIndex - rateStartIndex) << "|" << inputLine.substr(dstLabelsIndex) << std::endl;

                std::vector<std::string> dstLabels;
                StringTool::SplitString(inputLine.substr(dstLabelsIndex), ", ", dstLabels);

                int const srcId = GetValveId(inputLine[srcLabelIndex], inputLine[srcLabelIndex + 1]);
                m_rates[srcId] = atoi(inputLine.substr(rateStartIndex, rateEndIndex - rateStartIndex).c_str());
                m_tunnels[srcId].reserve(dstLabels.size());

                for (std::string const& dstLabel : dstLabels)
                {
                    m_tunnels[srcId].push_back(GetValveId(dstLabel[0], dstLabel[1]));
                }
            }
        }

        virtual void Run_PartOne() override
        {
            int const originValveId = GetValveId('A', 'A');

            std::set<int> workingValves;
            FindWorkingValves(workingValves);

            std::map<int, std::map<int, int>> directPaths;
            MapDirectPathsToImportantValves(originValveId, workingValves, directPaths);

            std::cout << FindBestPressureReleaseAmount(0, 30, originValveId, workingValves, directPaths) << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::cout << "WARNING: Part Two Not Implemented" << std::endl;
        }

        virtual void CleanUp() override {}

    private:
        int GetValveId(char const firstValveLabelChar, char const secondValveLabelChar) const
        {
            return static_cast<int>(firstValveLabelChar - 'A') * 100 + static_cast<int>(secondValveLabelChar - 'A');
        }

        std::string GetValveLabel(int const valveId) const
        {
            std::string label = "##";
            label[0] = static_cast<char>(valveId / 100) + 'A';
            label[1] = static_cast<char>(valveId % 100) + 'A';
            return label;
        }

        void FindWorkingValves(std::set<int>& outWorkingValves) const
        {
            outWorkingValves.clear();
            for (std::pair<int, int> const& ratePair : m_rates)
            {
                if (ratePair.second > 0)
                {
                    outWorkingValves.insert(ratePair.first);
                }
            }
        }

        void MapDirectPathsToImportantValves(int const originValveId, std::set<int> const& workingValves, std::map<int, std::map<int, int>>& directPaths) const
        {
            int pathCost = 0;
            for (int const dstValveId : workingValves)
            {
                if (FindShortestPath(originValveId, dstValveId, pathCost))
                {
                    directPaths[originValveId][dstValveId] = pathCost;
                }

                for (int const srcValveId : workingValves)
                {
                    if (srcValveId == dstValveId)
                    {
                        continue;
                    }

                    if (FindShortestPath(srcValveId, dstValveId, pathCost))
                    {
                        directPaths[srcValveId][dstValveId] = pathCost;
                    }
                }
            }
        }

        bool FindShortestPath(int const srcValveId, int const dstValveId, int& outPathCost) const
        {
            std::set<int> visitedValveIds;
            std::set<int> currentLayer;
            std::set<int> nextLayer;

            std::vector<int> const& srcDirectConnections = m_tunnels.find(srcValveId)->second;
            currentLayer.insert(srcDirectConnections.begin(), srcDirectConnections.end());

            outPathCost = 0;
            while (visitedValveIds.size() < m_tunnels.size())
            {
                ++outPathCost;
                for (int const& currentValveId : currentLayer)
                {
                    if (visitedValveIds.find(currentValveId) == visitedValveIds.end())
                    {
                        if (currentValveId == dstValveId)
                        {
                            return true;
                        }

                        std::vector<int> const& directConnections = m_tunnels.find(currentValveId)->second;
                        nextLayer.insert(directConnections.begin(), directConnections.end());

                        visitedValveIds.insert(currentValveId);
                    }
                }

                currentLayer.clear();
                currentLayer.insert(nextLayer.begin(), nextLayer.end());
                nextLayer.clear();
            }

            return false;
        }

        int FindBestPressureReleaseAmount(int const currentPressureAmount, int const remainingTime, int const currentValveId, std::set<int>& closedValves, std::map<int, std::map<int, int>> const& directPaths) const
        {
            if (remainingTime <= 0 || closedValves.size() == 0)
            {
                return currentPressureAmount;
            }

            std::map<int, int> const& srcDirectPaths = directPaths.find(currentValveId)->second;
            std::set<int> potentialValveIds = closedValves;

            int bestPressureAmount = currentPressureAmount;
            for (int const nextValveId : potentialValveIds)
            {
                auto const it = srcDirectPaths.find(nextValveId);
                int const pathCost = it != srcDirectPaths.end() ? it->second : remainingTime;
                int const nextRemainingTime = remainingTime - (pathCost + 1);

                if (nextRemainingTime > 0)
                {
                    int const valveRate = m_rates.find(nextValveId)->second;

                    closedValves.erase(nextValveId);
                    int const pressureAmount = FindBestPressureReleaseAmount(currentPressureAmount + nextRemainingTime * valveRate, nextRemainingTime, nextValveId, closedValves, directPaths);
                    closedValves.insert(nextValveId);

                    if (pressureAmount > bestPressureAmount)
                    {
                        bestPressureAmount = pressureAmount;
                    }
                }
            }

            return bestPressureAmount;
        }
    };
}
