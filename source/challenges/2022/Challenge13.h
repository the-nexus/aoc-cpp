#pragma once

#include "../ChallengeAbstract.h"
#include <memory>

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
            virtual bool IsVectorNode() const { return false; }
            virtual bool IsIntegerNode() const { return false; }
        };

        struct TreeNode_Vector final : public TreeNode
        {
            virtual bool IsVectorNode() const override { return true; }
            std::vector<TreeNode*> m_childNodes;
        };

        struct TreeNode_Integer final : public TreeNode
        {
            virtual bool IsIntegerNode() const override { return true; }
            int m_value = 0;
        };

        std::vector<std::pair<TreeNode*, TreeNode*>> m_nodePairs;

    public:
        virtual void SetUp(std::vector<std::string> const& inputLines) override
        {
            m_nodePairs.reserve((inputLines.size() + 1) / 3);
            for (size_t lineIndex = 0; lineIndex < inputLines.size(); ++lineIndex)
            {
                std::pair<TreeNode*, TreeNode*>& pair = m_nodePairs.emplace_back();
                pair.first = MakeTree(inputLines[lineIndex]);
                pair.second = MakeTree(inputLines[lineIndex + 1]);
            }
        }

        virtual void Run_PartOne() override
        {
            std::cout << "WARNING: Part One Not Implemented" << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::cout << "WARNING: Part Two Not Implemented" << std::endl;
        }

        virtual void CleanUp() override
        {
            for (std::pair<TreeNode*, TreeNode*>& nodePair : m_nodePairs)
            {
                DestroyTreeNode(nodePair.first);
                DestroyTreeNode(nodePair.second);
            }
        }

    private:
        TreeNode* MakeTree(std::string const& inputLine) const
        {
            return nullptr;
        }

        void DestroyTreeNode(TreeNode_Vector* vectorNode) const
        {

        }

        void DestroyTreeNode(TreeNode_Integer* integerNode) const
        {
            delete integerNode;
        }

        int CompareOrder(TreeNode_Integer* lhs, TreeNode_Integer rhs) const
        {
            if (lhs->m_value == rhs.m_value)
            {
                return 0;
            }
            else
            {
                return lhs->m_value < rhs.m_value ? -1 : 1;
            }
        }

        int CompareOrder(TreeNode_Vector* lhs, TreeNode_Vector* rhs) const
        {
            return 0;
        }

        int CompareOrder(TreeNode_Integer* lhs, TreeNode_Vector* rhs) const
        {
            TreeNode_Vector lhsVectorNode;
            lhsVectorNode.m_childNodes.push_back(lhs);
            return Compare(&lhsVectorNode, rhs);
        }

        int CompareOrder(TreeNode_Vector* lhs, TreeNode_Integer* rhs) const
        {
            TreeNode_Vector rhsVectorNode;
            rhsVectorNode.m_childNodes.push_back(lhs);
            return Compare(lhs, &rhsVectorNode);
        }
    };
}
