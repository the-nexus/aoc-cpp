#pragma once

#include "../ChallengeAbstract.h"
#include "../tools/VectorTool.h"

namespace Year2022
{
    class Challenge15 : public ChallengeAbstract
    {
    private:
        typedef std::pair<int, int> Range;

        struct Sensor
        {
            Vector2i m_position;
            Vector2i m_beaconPosition;
            int m_beaconDistance = 0;
        };

        std::vector<Sensor> m_sensors;

    public:
        virtual void SetUp(std::vector<std::string> const& inputLines) override
        {
            m_sensors.resize(inputLines.size());
            for (size_t lineIndex = 0; lineIndex < inputLines.size(); ++lineIndex)
            {
                std::string const& line = inputLines[lineIndex];
                Sensor& sensor = m_sensors[lineIndex];

                // Sensor pos
                size_t valStart = line.find_first_of("x=") + 2;
                size_t valEnd = line.find_first_of(',', valStart);
                sensor.m_position[0] = atoi(line.substr(valStart, valEnd - valStart).c_str());

                valStart = line.find_first_of("y=", valEnd) + 2;
                valEnd = line.find_first_of(':', valStart);
                sensor.m_position[1] = atoi(line.substr(valStart, valEnd - valStart).c_str());

                valStart = line.find_first_of("x=", valEnd) + 2;
                valEnd = line.find_first_of(',', valStart);
                sensor.m_beaconPosition[0] = atoi(line.substr(valStart, valEnd - valStart).c_str());

                valStart = line.find_first_of("y=", valEnd) + 2;
                valEnd = line.size();
                sensor.m_beaconPosition[1] = atoi(line.substr(valStart, valEnd - valStart).c_str());

                sensor.m_beaconDistance = Vector2i::ManhattanDistance(sensor.m_position, sensor.m_beaconPosition);
            }
        }

        virtual void Run_PartOne() override
        {
            int constexpr y = 2000000;

            std::vector<Range> coverageRanges;
            coverageRanges.reserve(m_sensors.size());

            FindCoverageRangesOnRow(y, coverageRanges);
            MergeCoverageRanges(coverageRanges);

            std::vector<int> beaconsOnRow;
            beaconsOnRow.reserve(m_sensors.size());
            for (Sensor const& sensor : m_sensors)
            {
                if (sensor.m_beaconPosition[1] == y && std::find(beaconsOnRow.begin(), beaconsOnRow.end(), sensor.m_beaconPosition[1]) == beaconsOnRow.end())
                {
                    beaconsOnRow.push_back(sensor.m_beaconPosition[1]);
                }
            }

            std::cout << (GetTotalCoverageSize(coverageRanges) - beaconsOnRow.size()) << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            int constexpr rangeMin = 0;
            int constexpr rangeMax = 4000000;

            unsigned long long frequency = 0;
            std::vector<Range> coverageRanges;
            coverageRanges.reserve(m_sensors.size());

            for (int y = rangeMin; y <= rangeMax; ++y)
            {
                coverageRanges.clear();
                FindCoverageRangesOnRow(y, coverageRanges);

                // Clamp the ranges
                for (Range& coverageRange : coverageRanges)
                {
                    if (coverageRange.first < rangeMin)
                    {
                        coverageRange.first = rangeMin;
                    }

                    if (coverageRange.second > rangeMax)
                    {
                        coverageRange.second = rangeMax;
                    }
                }

                MergeCoverageRanges(coverageRanges);

                if (GetTotalCoverageSize(coverageRanges) < rangeMax - rangeMin + 1)
                {
                    // There is either going to be 1 or 2 items (2 if the index is in between the 2 ranges), so X is at the limits of the first range in the list
                    int const x = coverageRanges[0].first == rangeMin ? coverageRanges[0].second + 1 : coverageRanges[0].first - 1;
                    frequency = static_cast<unsigned long long>(rangeMax) * static_cast<unsigned long long>(x) + static_cast<unsigned long long>(y);
                    break;
                }
            }

            std::cout << frequency << std::endl;
        }

        virtual void CleanUp() override {}

    private:
        void FindCoverageRangesOnRow(int const y, std::vector<Range>& outCoverageRanges) const
        {
            for (Sensor const& sensor : m_sensors)
            {
                // Check if row is in range of the sensor
                int const yDistance = abs(sensor.m_position[1] - y);
                if (yDistance <= sensor.m_beaconDistance)
                {
                    int const coverageHalfWidth = sensor.m_beaconDistance - yDistance;
                    outCoverageRanges.emplace_back(sensor.m_position[0] - coverageHalfWidth, sensor.m_position[0] + coverageHalfWidth);
                }
            }
        }

        void MergeCoverageRanges(std::vector<Range>& coverageRanges) const
        {
            // Merge overlapping ranges (loop over it until it has merged everything it could
            bool hasMergedAnything = true;
            while (hasMergedAnything)
            {
                hasMergedAnything = false;
                for (size_t lhsIndex = 0; lhsIndex < coverageRanges.size(); ++lhsIndex)
                {
                    for (size_t rhsIndex = 0; rhsIndex < coverageRanges.size(); ++rhsIndex)
                    {
                        if (lhsIndex == rhsIndex)
                        {
                            continue;
                        }

                        if (coverageRanges[lhsIndex].first <= coverageRanges[rhsIndex].first && coverageRanges[lhsIndex].second >= coverageRanges[rhsIndex].second)
                        {
                            // rhs is fully contained into lhs, remove rhs
                            std::swap(coverageRanges[rhsIndex--], coverageRanges.back());
                            coverageRanges.pop_back();
                            hasMergedAnything = true;
                            break;
                        }
                        else if (coverageRanges[lhsIndex].first <= coverageRanges[rhsIndex].second && coverageRanges[lhsIndex].second >= coverageRanges[rhsIndex].second)
                        {
                            // rhs is partially contained into lhs, adjust lhs and remove rhs
                            coverageRanges[lhsIndex].first = coverageRanges[rhsIndex].first;
                            std::swap(coverageRanges[rhsIndex--], coverageRanges.back());
                            coverageRanges.pop_back();
                            hasMergedAnything = true;
                            break;
                        }
                    }
                }
            }
        }

        int GetTotalCoverageSize(std::vector<Range> const& coverageRanges) const
        {
            int totalCoverageSize = 0;
            for (Range const& coverageRange : coverageRanges)
            {
                totalCoverageSize += coverageRange.second - coverageRange.first + 1;
            }
            return totalCoverageSize;
        }
    };
}
