
#pragma once

#include <set>

#include "Challenges/ChallengeAbstract.h"

namespace AOC::Challenges::Year2022
{
    class Challenge06 final : public ChallengeAbstract
    {
        std::string m_packet;

    public:
        Challenge06(std::vector<std::string> const& inputLines)
        {
            m_packet = inputLines[0];
        }

        virtual void Run_PartOne() override
        {
            std::cout << GetFirstMarkerIndex(4) << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::cout << GetFirstMarkerIndex(14) << std::endl;
        }

    private:
        size_t GetFirstMarkerIndex(size_t const sequenceSize) const
        {
            size_t lastSequenceStartIndex = 0;
            size_t uniqueByteCount = 0;
            for (size_t byteIndex = 0; byteIndex < m_packet.size(); ++byteIndex)
            {
                if (IsFirstByteOfRangeUnique(byteIndex, byteIndex + sequenceSize - 1 - uniqueByteCount))
                {
                    if (++uniqueByteCount == sequenceSize)
                    {
                        return byteIndex + 1;
                    }
                }
                else
                {
                    uniqueByteCount = 0;
                    byteIndex = lastSequenceStartIndex;
                    lastSequenceStartIndex = byteIndex + 1;
                }
            }

            return m_packet.size();
        }

        bool IsFirstByteOfRangeUnique(size_t testByteIndex, size_t const lastByteIndex) const
        {
            char const testByte = m_packet[testByteIndex++];
            for (; testByteIndex <= lastByteIndex && testByteIndex < m_packet.size(); ++testByteIndex)
            {
                if (testByte == m_packet[testByteIndex])
                {
                    return false;
                }
            }
            return true;
        }
    };
}
