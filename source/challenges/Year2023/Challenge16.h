#pragma once

#include "../ChallengeAbstract.h"
#include <GridTool.h>
#include <algorithm>

namespace Year2023
{
    class Challenge16 final : public ChallengeAbstract
    {
    private:

        enum class EDirection
        {
            None,
            Up,
            Down,
            Left,
            Right
        };

        struct BeamHead
        {
            Vector2sz m_position = Vector2sz();
            EDirection m_direction = EDirection::None;
        };

        GridTool::Grid<char> m_caveGrid;

    public:
        Challenge16(std::vector<std::string> const& inputLines)
        {
            m_caveGrid.Resize(inputLines.size() + 2, inputLines[0].size() + 2);
            m_caveGrid.ForEach([this, &inputLines](char& item, size_t const line, size_t const column)
                {
                    bool const isBorder =
                        line == 0 || line == (m_caveGrid.GetLineCount() - 1) ||
                        column == 0 || column == (m_caveGrid.GetColumnCount() - 1);

                    item = isBorder ? ' ' : inputLines[line - 1][column - 1];
                });
        }

        virtual void Run_PartOne() override
        {
            GridTool::Grid<unsigned int> coverageGrid;
            coverageGrid.Resize(m_caveGrid.GetDimensions());
            coverageGrid.SetAll(0);

            std::vector<BeamHead> heads;
            BeamHead& startingHead = heads.emplace_back();
            startingHead.m_position = Vector2sz(1, 1);
            startingHead.m_direction = EDirection::Right;

            bool hasActiveHead = true;
            while (hasActiveHead)
            {
                hasActiveHead = false;
                size_t const initialHeadCount = heads.size();

                for (size_t i = 0; i < initialHeadCount; ++i)
                {
                    if (heads[i].m_direction == EDirection::None)
                    {
                        continue;
                    }

                    hasActiveHead = true;
                    coverageGrid.WriteAt(heads[i].m_position) += 1;

                    MoveHead(heads[i]);

                    switch (m_caveGrid.ReadAt(heads[i].m_position))
                    {
                    case '/':
                        heads[i].m_direction = GetSlashReflectedDirection(heads[i].m_direction);
                        break;

                    case '\\':
                        heads[i].m_direction = GetBackslashReflectedDirection(heads[i].m_direction);
                        break;

                    case '-':
                        if (heads[i].m_direction == EDirection::Up || heads[i].m_direction == EDirection::Down)
                        {
                            BeamHead& newHead = heads.emplace_back();
                            SplitHorizontal(heads[i], newHead);
                        }
                        break;

                    case '|':
                        if (heads[i].m_direction == EDirection::Left || heads[i].m_direction == EDirection::Right)
                        {
                            BeamHead& newHead = heads.emplace_back();
                            SplitVertical(heads[i], newHead);
                        }
                        break;

                    case ' ':
                        Impact(heads[i]);
                        break;

                    default:
                        break;
                    }
                }
            }

            unsigned int coveredTileCount = 0;
            coverageGrid.ForEach([this, &coveredTileCount](unsigned int const& item, size_t const line, size_t const column)
                {
                    if (item > 0) ++coveredTileCount;

                    std::cout << (item > 0 ? '#' : '.');
                    if (column == m_caveGrid.GetColumnCount() - 1) std::cout << std::endl;
                });

            std::cout << coveredTileCount << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::cout << "WARNING: Part Two Not Implemented" << std::endl;
        }

    private:
        static void MoveHead(BeamHead& head)
        {
            switch (head.m_direction)
            {
            case EDirection::Up:        head.m_position[0] -= 1; break;
            case EDirection::Down:      head.m_position[0] += 1; break;
            case EDirection::Left:      head.m_position[1] -= 1; break;
            case EDirection::Right:     head.m_position[1] += 1; break;
            default: break;
            }
        }

        static EDirection GetSlashReflectedDirection(EDirection const direction)
        {
            switch (direction)
            {
            case EDirection::Up:        return EDirection::Right;
            case EDirection::Down:      return EDirection::Left;
            case EDirection::Left:      return EDirection::Down;
            case EDirection::Right:     return EDirection::Up;
            default:                    return EDirection::None;
            }
        }

        static EDirection GetBackslashReflectedDirection(EDirection const direction)
        {
            switch (direction)
            {
            case EDirection::Up:        return EDirection::Left;
            case EDirection::Down:      return EDirection::Right;
            case EDirection::Left:      return EDirection::Up;
            case EDirection::Right:     return EDirection::Down;
            default:                    return EDirection::None;
            }
        }

        static void SplitHorizontal(BeamHead& leftHead, BeamHead& rightHead)
        {
            leftHead.m_direction = EDirection::Left;
            rightHead.m_direction = EDirection::Right;
            rightHead.m_position = leftHead.m_position;
        }

        static void SplitVertical(BeamHead& upHead, BeamHead& downHead)
        {
            upHead.m_direction = EDirection::Up;
            downHead.m_direction = EDirection::Down;
            downHead.m_position = upHead.m_position;
        }

        static void Impact(BeamHead& head)
        {
            head.m_direction = EDirection::None;
        }
    };
}
