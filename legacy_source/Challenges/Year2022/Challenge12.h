
#pragma once

#include <algorithm>
#include <deque>
#include <map>

#include <Tools/Math/Vector.h>

#include "Challenges/ChallengeAbstract.h"

namespace AOC::Challenges::Year2022
{
    class Challenge12 final : public ChallengeAbstract
    {
    private:
        struct PathNode
        {
            Vector2i m_position = Vector2i();
            int m_heuristicCost = 0;
            int m_currentCost = 0;

            inline bool operator==(PathNode const& rhs) const { return m_position == rhs.m_position; }
            inline bool operator<(PathNode const& rhs) const { return m_currentCost + m_heuristicCost < rhs.m_currentCost + rhs.m_heuristicCost; }
        };

        int** m_heightMap = nullptr;
        Vector2i m_heightMapSize = Vector2i();
        Vector2i m_startPosition = Vector2i();
        Vector2i m_endPosition = Vector2i();

    public:
        Challenge12(std::vector<std::string> const& inputLines)
        {
            m_heightMapSize = Vector2i(static_cast<int>(inputLines[0].size()), static_cast<int>(inputLines.size()));
            m_heightMap = new int*[m_heightMapSize[0]];
            for (int x = 0; x < m_heightMapSize[0]; ++x)
            {
                m_heightMap[x] = new int[m_heightMapSize[1]];
                for (int y = 0; y < m_heightMapSize[1]; ++y)
                {
                    char const heightChar = inputLines[y][x];
                    if (inputLines[y][x] == 'S')
                    {
                        m_startPosition = Vector2i(x, y);
                        m_heightMap[x][y] = 0; // 'a'
                    }
                    else if (inputLines[y][x] == 'E')
                    {
                        m_endPosition = Vector2i(x, y);
                        m_heightMap[x][y] = 25; // 'z'
                    }
                    else
                    {
                        m_heightMap[x][y] = static_cast<int>(inputLines[y][x] - 'a');
                    }
                }
            }
        }

        ~Challenge12()
        {
            for (int x = 0; x < m_heightMapSize[0]; ++x)
            {
                delete m_heightMap[x];
            }
            delete m_heightMap;
        }

        virtual void Run_PartOne() override
        {
            std::deque<Vector2i> foundPath;
            FindShortestPath(m_startPosition, foundPath);

            std::cout << (foundPath.size() - 1) << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            size_t shortestPathSize = static_cast<size_t>(m_heightMapSize[0] * m_heightMapSize[1]);
            std::deque<Vector2i> foundPath;

            for (int x = 0; x < m_heightMapSize[0]; ++x)
            {
                for (int y = 0; y < m_heightMapSize[1]; ++y)
                {
                    if (m_heightMap[x][y] == 0)
                    {
                        foundPath.clear();
                        if (FindShortestPath(Vector2i(x, y), foundPath) && foundPath.size() < shortestPathSize)
                        {
                            shortestPathSize = foundPath.size();
                        }
                    }
                }
            }

            std::cout << shortestPathSize - 1 << std::endl;
        }

    private:
        bool FindShortestPath(Vector2i const& startPosition, std::deque<Vector2i>& outPath) const
        {
            std::map<Vector2i, PathNode> nodeParenting;
            std::deque<PathNode> potentialNodes;

            PathNode& startNode = potentialNodes.emplace_back();
            startNode.m_position = startPosition;
            nodeParenting[startPosition] = startNode;

            while (!potentialNodes.empty())
            {
                PathNode const currentNode = potentialNodes.front();
                potentialNodes.pop_front();

                if (currentNode.m_position == m_endPosition)
                {
                    break;
                }
                else
                {
                    AddPotentialNode(currentNode, Vector2i(currentNode.m_position[0], currentNode.m_position[1] + 1), potentialNodes, nodeParenting); // Up
                    AddPotentialNode(currentNode, Vector2i(currentNode.m_position[0], currentNode.m_position[1] - 1), potentialNodes, nodeParenting); // Down
                    AddPotentialNode(currentNode, Vector2i(currentNode.m_position[0] - 1, currentNode.m_position[1]), potentialNodes, nodeParenting); // Left
                    AddPotentialNode(currentNode, Vector2i(currentNode.m_position[0] + 1, currentNode.m_position[1]), potentialNodes, nodeParenting); // Right

                    std::sort(potentialNodes.begin(), potentialNodes.end());
                }
            }

            BuildPath(startPosition, nodeParenting, outPath);
            return outPath.front() == startPosition && outPath.back() == m_endPosition;
        }

        int GetHeuristicCost(Vector2i const& currentPosition) const
        {
            return Vector2i::ManhattanDistance(currentPosition, m_endPosition);
        }

        bool IsValidMove(Vector2i const& currentPosition, Vector2i const& nextPosition) const
        {
            if (nextPosition[0] < 0 || nextPosition[0] >= m_heightMapSize[0] ||
                nextPosition[1] < 0 || nextPosition[1] >= m_heightMapSize[1])
            {
                return false; // If out of bounds
            }

            if (m_heightMap[nextPosition[0]][nextPosition[1]] - m_heightMap[currentPosition[0]][currentPosition[1]] > 1)
            {
                return false; // If height difference is too high
            }

            return true;
        }

        void AddPotentialNode(PathNode const& currentNode, Vector2i const& potentialPosition, std::deque<PathNode>& potentialNodes, std::map<Vector2i, PathNode>& nodeParenting) const
        {
            if (IsValidMove(currentNode.m_position, potentialPosition) && nodeParenting.find(potentialPosition) == nodeParenting.end())
            {
                PathNode& potentialNode = potentialNodes.emplace_back();
                potentialNode.m_position = potentialPosition;
                potentialNode.m_heuristicCost = GetHeuristicCost(potentialPosition);
                potentialNode.m_currentCost = currentNode.m_currentCost + 1;

                nodeParenting[potentialPosition] = currentNode;
            }
        }

        void BuildPath(Vector2i const& startPosition, std::map<Vector2i, PathNode> const& nodeParenting, std::deque<Vector2i>& outPath) const
        {
            outPath.push_back(m_endPosition);
            auto it = nodeParenting.find(m_endPosition);

            while (it != nodeParenting.end())
            {
                outPath.push_front(it->second.m_position);
                it = it->second.m_position != startPosition ? nodeParenting.find(it->second.m_position) : nodeParenting.end();
            }
        }
    };
}
