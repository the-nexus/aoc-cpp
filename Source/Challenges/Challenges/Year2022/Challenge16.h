#pragma once

#include <map>
#include <set>

#include <Tools/StringSplitter.h>

#include "Challenges/ChallengeAbstract.h"

// TODO: Check out the Floyd-Warshall algorithm to maybe solve this faster
// https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm

namespace AOC::Challenges::Year2022
{
    class Challenge16 final : public ChallengeAbstract
    {
    private:
        struct Worker
        {
            Worker(int const startingValveId)
                : m_currentValveId(startingValveId)
                , m_currentRate(0)
                , m_remainingTravelTime(0)
                , m_releasedPressure(0)
            {}

            int m_currentValveId = 0;
            int m_currentRate = 0;
            int m_remainingTravelTime = 0;
            int m_releasedPressure = 0;
        };

        int m_startingValveId = 0;
        std::set<int> m_workingValves;
        std::map<int, int> m_valveRates;
        std::map<int, std::map<int, int>> m_directPaths;

    public:
        Challenge16(std::vector<std::string> const& inputLines)
        {
            m_startingValveId = GetValveId('A', 'A');

            std::map<int, std::vector<int>> paths;
            for (std::string const& inputLine : inputLines)
            {
                size_t const srcLabelIndex = inputLine.find_first_of(' ') + 1;
                size_t const rateStartIndex = inputLine.find_first_of('=', srcLabelIndex) + 1;
                size_t const rateEndIndex = inputLine.find_first_of(';', rateStartIndex);
                size_t const dstLabelsIndex = inputLine.find_first_of(' ', inputLine.find_last_of("valve")) + 1;

                std::vector<std::string> dstLabels;
                StringTool::SplitString(inputLine.substr(dstLabelsIndex), ", ", dstLabels);

                // Parse the info of the current valve
                int const srcId = GetValveId(inputLine[srcLabelIndex], inputLine[srcLabelIndex + 1]);
                int const srcRate = atoi(inputLine.substr(rateStartIndex, rateEndIndex - rateStartIndex).c_str());
                m_valveRates[srcId] = srcRate;
                if (srcRate > 0)
                {
                    m_workingValves.insert(srcId);
                }

                // Parse the destinations of the current valve
                paths[srcId].reserve(dstLabels.size());
                for (std::string const& dstLabel : dstLabels)
                {
                    paths[srcId].push_back(GetValveId(dstLabel[0], dstLabel[1]));
                }
            }

            // Map all the shortest path costs between the working valves (and starting valve towards working valves) to simplify execution
            int pathCost = 0;
            for (int const dstValveId : m_workingValves)
            {
                if (FindDirectPathCost(m_startingValveId, dstValveId, pathCost, paths))
                {
                    m_directPaths[m_startingValveId][dstValveId] = pathCost;
                }

                for (int const srcValveId : m_workingValves)
                {
                    if (srcValveId == dstValveId)
                    {
                        continue;
                    }

                    if (FindDirectPathCost(srcValveId, dstValveId, pathCost, paths))
                    {
                        m_directPaths[srcValveId][dstValveId] = pathCost;
                    }
                }
            }
        }

        virtual void Run_PartOne() override
        {
            std::set<int> closedValves = m_workingValves;
            std::vector<Worker> workers = { Worker(m_startingValveId) };

            std::cout << FindBestPressureRelease(30, workers, closedValves) << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::set<int> closedValves = m_workingValves;
            std::vector<Worker> workers = { Worker(m_startingValveId), Worker(m_startingValveId) };

            std::cout << FindBestPressureRelease(26, workers, closedValves) << std::endl;
        }

    private:
        int GetValveId(char const firstValveLabelChar, char const secondValveLabelChar) const
        {
            return (static_cast<int>(firstValveLabelChar - 'A') + 1) * 100 + static_cast<int>(secondValveLabelChar - 'A') + 1;
        }

        bool FindDirectPathCost(int const srcValveId, int const dstValveId, int& outPathCost, std::map<int, std::vector<int>> const& paths) const
        {
            std::set<int> visitedValveIds;
            std::set<int> currentLayer;
            std::set<int> nextLayer;

            std::vector<int> const& srcDirectConnections = paths.find(srcValveId)->second;
            currentLayer.insert(srcDirectConnections.begin(), srcDirectConnections.end());

            outPathCost = 0;
            while (visitedValveIds.size() < paths.size())
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

                        std::vector<int> const& directConnections = paths.find(currentValveId)->second;
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

        int FindBestPressureRelease(int const remainingTime, std::vector<Worker> workers, std::set<int>& closedValves) const
        {
            // Wait for any worker to be available
            int nextRemainingTime = remainingTime;
            while (nextRemainingTime > 0 && (closedValves.size() == 0 || !IsAnyWorkerAvailable(workers)))
            {
                --nextRemainingTime;
                for (Worker& worker : workers)
                {
                    --worker.m_remainingTravelTime;
                    worker.m_releasedPressure += worker.m_currentRate;

                    if (worker.m_remainingTravelTime == 0)
                    {
                        // Integrate the current valve's rate now that the travel time is achieved
                        worker.m_currentRate += m_valveRates.find(worker.m_currentValveId)->second;
                    }
                }
            }

            // Return the amount of pressure released up to now
            if (nextRemainingTime == 0)
            {
                int totalReleasedPressure = 0;
                for (Worker const& worker : workers)
                {
                    totalReleasedPressure += worker.m_releasedPressure;
                }
                return totalReleasedPressure;
            }

            // Process available workers with the current state
            std::set<int> potentialValveIds = closedValves;
            int bestPressureAmount = 0;

            for (Worker& worker : workers)
            {
                if (worker.m_remainingTravelTime > 0)
                {
                    continue;
                }

                int const currentValveId = worker.m_currentValveId;
                std::map<int, int> const& srcDirectPaths = m_directPaths.find(currentValveId)->second;

                for (int const nextValveId : potentialValveIds)
                {
                    auto const it = srcDirectPaths.find(nextValveId);
                    if (it == srcDirectPaths.end())
                    {
                        continue;
                    }

                    worker.m_currentValveId = nextValveId;
                    worker.m_remainingTravelTime = it->second + 1;

                    closedValves.erase(nextValveId);
                    int const pressureAmount = FindBestPressureRelease(nextRemainingTime, workers, closedValves);
                    closedValves.insert(nextValveId);

                    if (pressureAmount > bestPressureAmount)
                    {
                        bestPressureAmount = pressureAmount;
                    }
                }

                worker.m_currentValveId = currentValveId;
                worker.m_remainingTravelTime = 0;
            }

            return bestPressureAmount;
        }

        bool IsAnyWorkerAvailable(std::vector<Worker> const& workers) const
        {
            for (Worker const& worker : workers)
            {
                if (worker.m_remainingTravelTime == 0)
                {
                    return true;
                }
            }
            return false;
        }
    };
}
