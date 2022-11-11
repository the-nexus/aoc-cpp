#pragma once

#include "../ChallengeAbstract.h"

namespace Year2021
{
    class Challenge01 : public ChallengeAbstract
    {
    public:
        virtual void SetUp(std::vector<std::string> const& inputLines) override
        {
            m_measurements.resize(inputLines.size());
            for (size_t idx = 0; idx < inputLines.size(); ++idx)
            {
                m_measurements[idx] = atoi(inputLines[idx].c_str());
            }
        }

        virtual void Run_PartOne() override
        {
            int largerMeasurementsCount = 0;
            int lastMeasurement = m_measurements[0];

            for (size_t idx = 1; idx < m_measurements.size(); ++idx)
            {
                int measurement = m_measurements[idx];
                if (measurement > lastMeasurement)
                {
                    ++largerMeasurementsCount;
                }

                lastMeasurement = measurement;
            }

            std::cout << largerMeasurementsCount << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            int largerMeasurementWindowsCount = 0;
            int lastMeasurementWindow = m_measurements[0] + m_measurements[1] + m_measurements[2];

            for (size_t idx = 3; idx < m_measurements.size(); ++idx)
            {
                int measurementWindow = lastMeasurementWindow + m_measurements[idx] - m_measurements[idx - 3];
                if (measurementWindow > lastMeasurementWindow)
                {
                    ++largerMeasurementWindowsCount;
                }

                lastMeasurementWindow = measurementWindow;
            }

            std::cout << largerMeasurementWindowsCount << std::endl;
        }

        virtual void CleanUp() override
        {

        }

    private:
        std::vector<int> m_measurements;
    };
}
