#pragma once

#include "../ChallengeAbstract.h"
#include <iostream>

namespace Year2022
{
    class Challenge13 : public ChallengeAbstract
    {
    private:
        enum class EOrderResult
        {
            Unknown,
            Ordered,
            NotOrdered
        };

        struct TreeNode
        {
            virtual void Destroy() { delete this; }
            virtual EOrderResult CompareOrder(TreeNode const* rhs) const = 0;
        };

        struct TreeNode_Vector final : public TreeNode
        {
            virtual void Destroy() override
            {
                for (TreeNode* childNode : m_childNodes)
                {
                    childNode->Destroy();
                }

                TreeNode::Destroy();
            }

            virtual EOrderResult CompareOrder(TreeNode const* rhs) const override
            {
                if (TreeNode_Integer const* rhsInteger = dynamic_cast<TreeNode_Integer const*>(rhs))
                {
                    TreeNode_Vector rhsVector;
                    rhsVector.m_childNodes.push_back(const_cast<TreeNode_Integer*>(rhsInteger));
                    return CompareOrder(&rhsVector);
                }
                else if (TreeNode_Vector const* rhsVector = dynamic_cast<TreeNode_Vector const*>(rhs))
                {
                    return CompareOrder(rhsVector);
                }
                else
                {
                    return EOrderResult::Unknown;
                }
            }

            EOrderResult CompareOrder(TreeNode_Vector const* rhs) const
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
                
                if (m_childNodes.size() < rhs->m_childNodes.size())
                {
                    return EOrderResult::Unknown;
                }
                else
                {
                    return isLhsSmaller ? EOrderResult::Ordered : EOrderResult::NotOrdered;
                }
            }

            std::vector<TreeNode*> m_childNodes;

            std::ostream& operator<<(std::ostream& os)
            {
                os << "[";
                for (size_t nodeIndex = 0; nodeIndex < m_childNodes.size(); ++nodeIndex)
                {
                    if (nodeIndex != 0)
                    {
                        os << ',';
                    }
                    os << m_childNodes[nodeIndex];
                }
                os << "]";
                return os;
            }
        };

        struct TreeNode_Integer final : public TreeNode
        {
            virtual EOrderResult CompareOrder(TreeNode const* rhs) const override
            {
                if (TreeNode_Integer const* rhsInteger = dynamic_cast<TreeNode_Integer const*>(rhs))
                {
                    return CompareOrder(rhsInteger);
                }
                else if (TreeNode_Vector const* rhsVector = dynamic_cast<TreeNode_Vector const*>(rhs))
                {
                    TreeNode_Vector lhsVector;
                    lhsVector.m_childNodes.push_back(const_cast<TreeNode_Integer*>(this));
                    return lhsVector.CompareOrder(rhsVector);
                }
                else
                {
                    return EOrderResult::Unknown;
                }
            }

            EOrderResult CompareOrder(TreeNode_Integer const* rhs) const
            {
                return m_value < rhs->m_value ? EOrderResult::Ordered : EOrderResult::Unknown;
            }

            int m_value = 0;

            std::ostream& operator<<(std::ostream& os)
            {
                os << m_value;
                return os;
            }
        };

        std::vector<std::pair<TreeNode*, TreeNode*>> m_nodePairs;

    public:
        virtual void SetUp(std::vector<std::string> const& inputLines) override
        {
            m_nodePairs.reserve((inputLines.size() + 1) / 3);
            for (size_t lineIndex = 0; lineIndex < 1/*inputLines.size()*/; ++lineIndex)
            {
                TreeNode* node = MakeTree(inputLines[lineIndex]);
                std::cout << node << std::endl;
                delete node;

                // std::pair<TreeNode*, TreeNode*>& pair = m_nodePairs.emplace_back();
                // pair.first = MakeTree(inputLines[lineIndex]);
                // pair.second = MakeTree(inputLines[lineIndex + 1]);

                // std::cout << pair.first << std::endl;
                // std::cout << pair.second << std::endl << std::endl;
            }
        }

        virtual void Run_PartOne() override
        {
            size_t orderedPairIndexSum = 0;
            for (size_t pairIndex = 0; pairIndex < m_nodePairs.size(); ++pairIndex)
            {
                if (m_nodePairs[pairIndex].first->CompareOrder(m_nodePairs[pairIndex].second) == EOrderResult::Ordered)
                {
                    orderedPairIndexSum += pairIndex + 1;
                }
            }
            std::cout << orderedPairIndexSum << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::cout << "WARNING: Part Two Not Implemented" << std::endl;
        }

        virtual void CleanUp() override
        {
            for (std::pair<TreeNode*, TreeNode*>& nodePair : m_nodePairs)
            {
                nodePair.first->Destroy();
                nodePair.second->Destroy();
            }
        }

    private:
        TreeNode* MakeTree(std::string const& inputLine) const
        {
            size_t inputCharIndex = 0;
            return MakeVectorNode(inputLine, inputCharIndex);
        }

        TreeNode_Vector* MakeVectorNode(std::string const& inputLine, size_t& inputCharIndex) const
        {
            TreeNode_Vector* vectorNode = new TreeNode_Vector;
            while (inputLine[++inputCharIndex] != ']')
            {
                std::cout << inputLine[inputCharIndex];
                if (inputLine[inputCharIndex] == '[')
                {
                    vectorNode->m_childNodes.push_back(MakeVectorNode(inputLine, inputCharIndex));
                }
                else if (inputLine[inputCharIndex] == ',')
                {
                    continue;
                }
                else
                {
                    vectorNode->m_childNodes.push_back(MakeIntegerNode(inputLine, inputCharIndex));
                }
            }
            return vectorNode;

        }

        TreeNode_Integer* MakeIntegerNode(std::string const& inputLine, size_t& inputCharIndex) const
        {
            TreeNode_Integer* integerNode = new TreeNode_Integer;
            while (inputLine[inputCharIndex] != ',' && inputLine[inputCharIndex] != ']')
            {
                int const charValue = static_cast<int>(inputLine[inputCharIndex++] - '0');
                integerNode->m_value = integerNode->m_value * 10 + charValue;
            }
            return integerNode;
        }
    };
}
