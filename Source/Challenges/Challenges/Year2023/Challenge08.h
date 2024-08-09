
#pragma once

#include <map>

#include "Challenges/ChallengeAbstract.h"

namespace AOC::Challenges::Year2023
{
    class Challenge08 final : public ChallengeAbstract
    {
    private:
        typedef unsigned int NodeId;

        struct Node
        {
            std::string m_label = "AAA";
            NodeId m_leftId = 0;
            NodeId m_rightId = 0;
        };

        std::map<NodeId, Node> m_nodeMap;
        std::string m_path;

    public:
        Challenge08(std::vector<std::string> const& inputLines)
        {
            auto it = inputLines.begin();
            m_path = *it;

            for (it += 2; it < inputLines.cend(); ++it)
            {
                Node node;
                node.m_label = it->substr(0, 3);
                node.m_leftId = GetNodeId(it->substr(7, 3));
                node.m_rightId = GetNodeId(it->substr(12, 3));

                NodeId const id = GetNodeId(node.m_label);
                m_nodeMap.emplace(id, node);
            }
        }

        virtual void Run_PartOne() override
        {
            NodeId currentNodeId = GetNodeId("AAA");
            NodeId targetNodeId = GetNodeId("ZZZ");

            size_t stepCount = 0;
            //while (currentNodeId != targetNodeId)
            //{
            //    char const token = m_path[stepCount++ % m_path.size()];
            //    currentNodeId = token == 'L' ? m_nodeMap[currentNodeId].m_leftId : m_nodeMap[currentNodeId].m_rightId;
            //}

            std::cout << stepCount << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::vector<NodeId> currentNodeIds;
            currentNodeIds.reserve(m_nodeMap.size());
            for (std::pair<NodeId, Node> nodePair : m_nodeMap)
            {
                if (nodePair.first % 100 == 0) // id == ??A
                {
                    currentNodeIds.push_back(nodePair.first);
                }
            }

            size_t stepCount = 0;
            bool areAllNodesAtTarget = false;

            while (!areAllNodesAtTarget)
            {
                char const token = m_path[stepCount++ % m_path.size()];
                areAllNodesAtTarget = true;

                for (NodeId& currentNodeId : currentNodeIds)
                {
                    currentNodeId = token == 'L' ? m_nodeMap[currentNodeId].m_leftId : m_nodeMap[currentNodeId].m_rightId;
                    areAllNodesAtTarget &= currentNodeId % 100 == 25; // id == ??Z
                }
            }

            std::cout << stepCount << std::endl;
        }

    private:
        static NodeId GetNodeId(std::string const& nodeLabel)
        {
            NodeId nodeId = 0;
            for (char const token : nodeLabel)
            {
                nodeId = nodeId * 100 + static_cast<int>(token - 'A');
            }
            return nodeId;
        }
    };
}
