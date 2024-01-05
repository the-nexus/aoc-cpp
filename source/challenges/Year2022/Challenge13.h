#pragma once

#include "../ChallengeAbstract.h"
#include <algorithm>
#include <iostream>

namespace Year2022
{
    class Challenge13 final : public ChallengeAbstract
    {
    private:
        enum class EOrderResult
        {
            Unknown,
            Ordered,
            NotOrdered
        };

        struct PacketNode
        {
            virtual void Destroy() { delete this; }
            virtual EOrderResult CompareOrder(PacketNode const* rhs) const = 0;
        };

        struct PacketNode_Vector final : public PacketNode
        {
            virtual void Destroy() override
            {
                for (PacketNode* childNode : m_childNodes)
                {
                    childNode->Destroy();
                }

                PacketNode::Destroy();
            }

            virtual EOrderResult CompareOrder(PacketNode const* rhs) const override
            {
                if (PacketNode_Integer const* rhsInteger = dynamic_cast<PacketNode_Integer const*>(rhs))
                {
                    PacketNode_Vector rhsVector;
                    rhsVector.m_childNodes.push_back(const_cast<PacketNode_Integer*>(rhsInteger));
                    return CompareOrder(&rhsVector);
                }
                else if (PacketNode_Vector const* rhsVector = dynamic_cast<PacketNode_Vector const*>(rhs))
                {
                    return CompareOrder(rhsVector);
                }
                else
                {
                    return EOrderResult::Unknown;
                }
            }

            EOrderResult CompareOrder(PacketNode_Vector const* rhs) const
            {
                bool const isLhsSmaller = m_childNodes.size() < rhs->m_childNodes.size();
                size_t const commonSize = isLhsSmaller ? m_childNodes.size() : rhs->m_childNodes.size();

                for (size_t nodeIndex = 0; nodeIndex < commonSize; ++nodeIndex)
                {
                    EOrderResult const orderResult = m_childNodes[nodeIndex]->CompareOrder(rhs->m_childNodes[nodeIndex]);
                    if (orderResult != EOrderResult::Unknown)
                    {
                        return orderResult;
                    }
                }
                
                if (m_childNodes.size() == rhs->m_childNodes.size())
                {
                    return EOrderResult::Unknown;
                }
                else
                {
                    return isLhsSmaller ? EOrderResult::Ordered : EOrderResult::NotOrdered;
                }
            }

            std::vector<PacketNode*> m_childNodes;
        };

        struct PacketNode_Integer final : public PacketNode
        {
            virtual EOrderResult CompareOrder(PacketNode const* rhs) const override
            {
                if (PacketNode_Integer const* rhsInteger = dynamic_cast<PacketNode_Integer const*>(rhs))
                {
                    return CompareOrder(rhsInteger);
                }
                else if (PacketNode_Vector const* rhsVector = dynamic_cast<PacketNode_Vector const*>(rhs))
                {
                    PacketNode_Vector lhsVector;
                    lhsVector.m_childNodes.push_back(const_cast<PacketNode_Integer*>(this));
                    return lhsVector.CompareOrder(rhsVector);
                }
                else
                {
                    return EOrderResult::Unknown;
                }
            }

            EOrderResult CompareOrder(PacketNode_Integer const* rhs) const
            {
                if (m_value == rhs->m_value)
                {
                    return EOrderResult::Unknown;
                }
                else
                {
                    return m_value < rhs->m_value ? EOrderResult::Ordered : EOrderResult::NotOrdered;
                }
            }

            int m_value = 0;
        };

        std::vector<PacketNode*> m_packets;

    public:
        Challenge13(std::vector<std::string> const& inputLines)
        {
            m_packets.reserve((inputLines.size() + 1) / 3);
            for (size_t lineIndex = 0; lineIndex < inputLines.size(); lineIndex += 3)
            {
                m_packets.push_back(MakePacket(inputLines[lineIndex]));
                m_packets.push_back(MakePacket(inputLines[lineIndex + 1]));
            }
        }

        ~Challenge13()
        {
            for (PacketNode* packet : m_packets)
            {
                packet->Destroy();
            }
        }

        virtual void Run_PartOne() override
        {
            size_t orderedPairIndexSum = 0;
            for (size_t pairIndex = 0; pairIndex < m_packets.size(); pairIndex += 2)
            {
                if (m_packets[pairIndex]->CompareOrder(m_packets[pairIndex + 1]) == EOrderResult::Ordered)
                {
                    orderedPairIndexSum += pairIndex / 2 + 1;
                }
            }
            std::cout << orderedPairIndexSum << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            m_packets.push_back(MakePacket("[[2]]"));
            PacketNode const* firstDivider = m_packets.back();

            m_packets.push_back(MakePacket("[[6]]"));
            PacketNode const* secondDivider = m_packets.back();

            std::sort(m_packets.begin(), m_packets.end(), [](PacketNode const* lhs, PacketNode const* rhs) -> bool {
                return lhs->CompareOrder(rhs) == EOrderResult::Ordered;
            });

            size_t firstDividerIndex = 0;
            for (; firstDividerIndex < m_packets.size(); ++firstDividerIndex)
            {
                if (m_packets[firstDividerIndex] == firstDivider)
                {
                    break;
                }
            }

            size_t secondDividerIndex = firstDividerIndex + 1;
            for (; secondDividerIndex < m_packets.size(); ++secondDividerIndex)
            {
                if (m_packets[secondDividerIndex] == secondDivider)
                {
                    break;
                }
            }

            std::cout << ((firstDividerIndex + 1) * (secondDividerIndex + 1)) << std::endl;
        }

    private:
        PacketNode* MakePacket(std::string const& inputLine) const
        {
            size_t inputCharIndex = 0;
            return MakeVectorNode(inputLine, inputCharIndex);
        }

        PacketNode_Vector* MakeVectorNode(std::string const& inputLine, size_t& inputCharIndex) const
        {
            PacketNode_Vector* vectorNode = new PacketNode_Vector;
            while (inputLine[inputCharIndex] != ']')
            {
                if (inputLine[++inputCharIndex] == '[')
                {
                    vectorNode->m_childNodes.push_back(MakeVectorNode(inputLine, inputCharIndex));
                }
                else if (inputLine[inputCharIndex] >= '0' && inputLine[inputCharIndex] <= '9')
                {
                    vectorNode->m_childNodes.push_back(MakeIntegerNode(inputLine, inputCharIndex));
                }
            }
            ++inputCharIndex;
            return vectorNode;

        }

        PacketNode_Integer* MakeIntegerNode(std::string const& inputLine, size_t& inputCharIndex) const
        {
            PacketNode_Integer* integerNode = new PacketNode_Integer;
            while (inputLine[inputCharIndex] != ',' && inputLine[inputCharIndex] != ']')
            {
                int const charValue = static_cast<int>(inputLine[inputCharIndex++] - '0');
                integerNode->m_value = integerNode->m_value * 10 + charValue;
            }
            return integerNode;
        }
    };
}
