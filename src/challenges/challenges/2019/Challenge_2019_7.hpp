
#pragma once

#include <algorithm>
#include <vector>

#include "challenges/Challenge.hpp"
#include "challenges/2019/intcode/Computer.hpp"
#include "challenges/2019/intcode/io/IOQueue.hpp"

namespace aoc::challenges
{
    class Challenge_2019_7 final : public Challenge<2019, 7>
    {
        using Super = Challenge<2019, 7>;

        using ComputerT = intcode2019::Computer;
        using PipeT = intcode2019::IOQueue;
        using DataT = intcode2019::data_t;

    public:
        Challenge_2019_7(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines)) 
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            std::vector<DataT> phases = { 0, 1, 2, 3, 4 };
            FindBestSignal(phases, false);

            for (DataT const& phase : phases)
            {
                outAnswer << phase;
            }
        }

        void RunPartTwo(std::ostream& outAnswer) override 
        {
            std::vector<DataT> phases = { 5, 6, 7, 8, 9 };
            DataT const bestSignal = FindBestSignal(phases, true);

            outAnswer << bestSignal;
        }

    private:
        DataT FindBestSignal(std::vector<DataT>& outBestPhases, bool const isFeedbackLoop)
        {
            std::vector<DataT> const programData = ComputerT::CompileProgram(GetInputLine(0));

            std::vector<ComputerT> computers;
            //computers.reserve(5);

            computers.emplace_back(programData);
            computers.emplace_back(programData);
            computers.emplace_back(programData);
            computers.emplace_back(programData);
            computers.emplace_back(programData);

            std::vector<PipeT> dataPipes;
            dataPipes.resize(isFeedbackLoop ? 5 : 6);

            computers[0].SetInputPipe(&dataPipes[0]);
            computers[0].SetOutputPipe(&dataPipes[1]);
            computers[1].SetInputPipe(&dataPipes[1]);
            computers[1].SetOutputPipe(&dataPipes[2]);
            computers[2].SetInputPipe(&dataPipes[2]);
            computers[2].SetOutputPipe(&dataPipes[3]);
            computers[3].SetInputPipe(&dataPipes[3]);
            computers[3].SetOutputPipe(&dataPipes[4]);
            computers[4].SetInputPipe(&dataPipes[4]);
            computers[4].SetOutputPipe(isFeedbackLoop ? &dataPipes[0] : &dataPipes[5]);

            DataT bestSignal = 0;
            std::vector<DataT> phases = outBestPhases;

            do
            {
                InitializeComputers(phases, computers, dataPipes);
                RunComputers(computers);

                PipeT& dataOut = isFeedbackLoop ? dataPipes.front() : dataPipes.back();
                DataT finalSignal = 0;

                while (dataOut.ReadData(finalSignal)) {}

                if (finalSignal > bestSignal)
                {
                    bestSignal = finalSignal;
                    outBestPhases = phases;
                }
            }
            while (std::next_permutation(std::begin(phases), std::end(phases)));

            return bestSignal;
        }

        static void InitializeComputers(std::vector<DataT> const& phases, std::vector<ComputerT>& computers, std::vector<PipeT>& dataPipes)
        {
            for (ComputerT& computer : computers)
            {
                computer.Reset();
            }

            for (size_t phaseIndex = 0; phaseIndex < phases.size(); ++phaseIndex)
            {
                dataPipes[phaseIndex].WriteData(phases[phaseIndex]);
            }

            dataPipes.front().WriteData(0);
        }

        static void RunComputers(std::vector<ComputerT>& computers)
        {
            bool hasEveryComputerHalted;
            do
            {
                hasEveryComputerHalted = true;
                for (ComputerT& computer : computers)
                {
                    if (computer.HasHalted())
                    {
                        continue;
                    }

                    hasEveryComputerHalted = false;
                    computer.Step();
                }
            }
            while (hasEveryComputerHalted);
        }
    };
}
