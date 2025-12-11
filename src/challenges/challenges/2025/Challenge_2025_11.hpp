
#pragma once

#include <algorithm>
#include <map>
#include <optional>

#include "challenges/Challenge.hpp"

namespace aoc::challenges
{
    class Challenge_2025_11 final : public Challenge<2025, 11>
    {
        using Super = Challenge<2025, 11>;
        using MachineID = unsigned int;

        struct Machine
        {
            MachineID _id = 0;
            std::vector<Machine*> _outputMachines;
        };

        struct MachineFinder
        {
            MachineFinder(const MachineID machineID) : _machineID(machineID) {}
            bool operator()(const Machine& machine) const { return machine._id == _machineID; }

            MachineID _machineID = 0;
        };

    public:
        Challenge_2025_11(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines))
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            std::vector<Machine> machines;
            BuildMachines(machines);

            size_t pathCount = 0;

            const MachineID youMachineID = ToMachineID('y', 'o', 'u');
            const MachineID outMachineID = ToMachineID('o', 'u', 't');

            const auto youMachineIt = std::find_if(std::cbegin(machines), std::cend(machines), MachineFinder{ youMachineID });
            if (youMachineIt != std::cend(machines))
            {
                std::map<MachineID, size_t> pathsToOut;
                pathCount = CountPaths(*youMachineIt, outMachineID, pathsToOut);
            }

            outAnswer << pathCount;
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            std::vector<Machine> machines;
            BuildMachines(machines);

            size_t pathCount = 0;

            const MachineID svrMachineID = ToMachineID('s', 'v', 'r');
            const MachineID fftMachineID = ToMachineID('f', 'f', 't');
            const MachineID dacMachineID = ToMachineID('d', 'a', 'c');
            const MachineID outMachineID = ToMachineID('o', 'u', 't');

            const auto svrMachineIt = std::find_if(std::cbegin(machines), std::cend(machines), MachineFinder{ svrMachineID });
            if (svrMachineIt != std::cend(machines))
            {
                std::map<MachineID, size_t> pathsFromSvrToFft;
                size_t svrToFftPathCount = CountPaths(*svrMachineIt, fftMachineID, pathsFromSvrToFft, dacMachineID);

                const auto fftMachineIt = std::find_if(std::cbegin(machines), std::cend(machines), MachineFinder{ fftMachineID });
                const auto dacMachineIt = std::find_if(std::cbegin(machines), std::cend(machines), MachineFinder{ dacMachineID });

                if (fftMachineIt != std::cend(machines))
                {
                    std::map<MachineID, size_t> pathsFromFftToDac;
                    size_t fftToDacPathCount = CountPaths(*fftMachineIt, dacMachineID, pathsFromFftToDac);
                    svrToFftPathCount *= fftToDacPathCount;

                    if (dacMachineIt != std::cend(machines))
                    {
                        std::map<MachineID, size_t> pathsFromDacToOut;
                        size_t dacToOutPathCount = CountPaths(*dacMachineIt, outMachineID, pathsFromDacToOut, fftMachineID);
                        svrToFftPathCount *= dacToOutPathCount;
                    }
                }

                std::map<MachineID, size_t> pathsFromSvrToDac;
                size_t svrToDacPathCount = CountPaths(*svrMachineIt, dacMachineID, pathsFromSvrToDac, fftMachineID);

                if (dacMachineIt != std::cend(machines))
                {
                    std::map<MachineID, size_t> pathsFromDacToFft;
                    size_t dacToFftPathCount = CountPaths(*dacMachineIt, fftMachineID, pathsFromDacToFft);
                    svrToDacPathCount *= dacToFftPathCount;

                    if (fftMachineIt != std::cend(machines))
                    {
                        std::map<MachineID, size_t> pathsFromFftToOut;
                        size_t fftToOutPathCount = CountPaths(*fftMachineIt, outMachineID, pathsFromFftToOut, dacMachineID);
                        svrToDacPathCount *= fftToOutPathCount;
                    }
                }

                pathCount = svrToFftPathCount + svrToDacPathCount;
            }

            outAnswer << pathCount;
        }

    private:
        void BuildMachines(std::vector<Machine>& outMachines) const
        {
            const std::vector<std::string>& lines = GetInputLines();
            outMachines.reserve(lines.size() + 1);

            std::map<MachineID, Machine*> machineMap;

            for (const std::string& line : lines)
            {
                const MachineID machineID = ToMachineID(line[0], line[1], line[2]);

                Machine& machine = CreateOrGetMachine(machineID, machineMap, outMachines);
                machine._outputMachines.reserve((line.size() / 4) - 1);

                for (size_t charIndex = 5; charIndex < line.size(); charIndex += 4)
                {
                    const MachineID outputMachineID = ToMachineID(line[charIndex], line[charIndex + 1], line[charIndex + 2]);

                    Machine& outputMachine = CreateOrGetMachine(outputMachineID, machineMap, outMachines);
                    machine._outputMachines.push_back(&outputMachine);
                }
            }
        }

        static MachineID ToMachineID(char leftChar, const char centerChar, const char rightChar)
        {
            const MachineID leftID = static_cast<MachineID>(leftChar) << 16;
            const MachineID centerID = static_cast<MachineID>(centerChar) << 8;
            const MachineID rightID = static_cast<MachineID>(rightChar);
            return leftID | centerID | rightID;
        }

        static Machine& CreateOrGetMachine(const MachineID machineID, std::map<MachineID, Machine*>& machineMap, std::vector<Machine>& outMachines)
        {
            const auto machineIt = machineMap.find(machineID);
            if (machineIt != machineMap.end())
            {
                return *machineIt->second;
            }

            Machine& machine = outMachines.emplace_back();
            machine._id = machineID;

            machineMap.emplace(machineID, &machine);

            return machine;
        }

        static size_t CountPaths(const Machine& srcMachine, const MachineID& dstMachineID, std::map<MachineID, size_t>& pathsToDst, const std::optional<MachineID>& ignoredMachineID = std::nullopt)
        {
            const auto [pathIt, hasEmplaced] = pathsToDst.try_emplace(srcMachine._id, 0);
            if (!hasEmplaced)
            {
                // Already processed, return cached path count
                return pathIt->second;
            }

            if (srcMachine._id == dstMachineID)
            {
                // Returns 1
                return ++pathIt->second;
            }

            if (ignoredMachineID.has_value() && srcMachine._id == ignoredMachineID)
            {
                // Returns 0
                return pathIt->second;
            }

            for (const Machine* outputMachine : srcMachine._outputMachines)
            {
                pathIt->second += CountPaths(*outputMachine, dstMachineID, pathsToDst);
            }

            return pathIt->second;
        }
    };
}
