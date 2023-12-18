#pragma once

#include "../ChallengeAbstract.h"
#include <GridTool.h>
#include <StringTool.h>
#include <VectorTool.h>

namespace Year2023
{
    class Challenge18 : public ChallengeAbstract
    {
        typedef VectorTool::Vector3<uint8_t> Color;

        enum class EDirection
        {
            None,
            Up,
            Down,
            Left,
            Right
        };

        struct DiggingInstriction
        {
            EDirection m_direction = EDirection::None;
            unsigned int m_steps = 0;
            Color m_color;
        };

        std::vector<DiggingInstriction> m_instructions;
        GridTool::Grid<Color const*> m_colorGrid;
        Vector2sz m_startPosition;

    public:
        virtual void SetUp(std::vector<std::string> const& inputLines) override
        {
            m_instructions.reserve(inputLines.size());
            for (std::string const& line : inputLines)
            {
                std::vector<std::string> lineSplit;
                StringTool::SplitString(line, ' ', lineSplit);

                DiggingInstriction& instruction = m_instructions.emplace_back();
                instruction.m_direction = GetDirectionFromChar(lineSplit[0][0]);
                instruction.m_steps = atoi(lineSplit[1].c_str());
                instruction.m_color = GetColorFromHexString(lineSplit[2].substr(2, 6));
            }

            Vector2i minPos(0);
            Vector2i maxPos(0);
            Vector2i pos(0);

            for (DiggingInstriction const& instruction : m_instructions)
            {
                AdvanceDigger(instruction.m_direction, instruction.m_steps, pos);
                if (pos[0] < minPos[0]) minPos[0] = pos[0];
                if (pos[0] > maxPos[0]) maxPos[0] = pos[0];
                if (pos[1] < minPos[1]) minPos[1] = pos[1];
                if (pos[1] > maxPos[1]) maxPos[1] = pos[1];
            }

            m_startPosition = Vector2sz(
                static_cast<size_t>(-minPos[0]),
                static_cast<size_t>(-minPos[1])
            );

            m_colorGrid.Resize(
                static_cast<size_t>(maxPos[0] - minPos[0] + 1),
                static_cast<size_t>(maxPos[1] - minPos[1] + 1)
            );
            m_colorGrid.SetAll(nullptr);

            Vector2sz diggerPosition = m_startPosition;
            for (DiggingInstriction const& instruction : m_instructions)
            {
                for (unsigned int step = 0; step < instruction.m_steps; ++step)
                {
                    AdvanceDigger(instruction.m_direction, 1, diggerPosition);
                    m_colorGrid.WriteAt(diggerPosition) = &instruction.m_color;
                }
            }
        }

        virtual void Run_PartOne() override
        {
            GridTool::Grid<Color const*> filledColorGrid = m_colorGrid;
            std::unique_ptr<Color> fillColor = std::make_unique<Color>(UINT8_MAX);

            Vector2sz startPos = Vector2sz(0, 0);
            while (filledColorGrid.ReadAt(startPos) == nullptr)
            {
                ++startPos[0];
            }
            startPos += 1;

            Flood(filledColorGrid, fillColor.get(), startPos);

            filledColorGrid.ForEach([&filledColorGrid](Color const* color, size_t const line, size_t const column)
                {
                    std::cout << (color ? '#' : '.');
                    if (column == filledColorGrid.GetColumnCount() - 1) std::cout << std::endl;
                });

            std::cout << "WARNING: Part One Not Implemented" << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::cout << "WARNING: Part Two Not Implemented" << std::endl;
        }

        virtual void CleanUp() override {}

    private:
        static EDirection GetDirectionFromChar(char const token)
        {
            switch (token)
            {
            case 'U': return EDirection::Up;
            case 'D': return EDirection::Down;
            case 'L': return EDirection::Left;
            case 'R': return EDirection::Right;
            default:  return EDirection::None;
            }
        }

        static Color GetColorFromHexString(std::string const& colorStr)
        {
            return Color(
                static_cast<uint8_t>((GetHexValueFromChar(colorStr[0]) << 4) + GetHexValueFromChar(colorStr[1])),
                static_cast<uint8_t>((GetHexValueFromChar(colorStr[2]) << 4) + GetHexValueFromChar(colorStr[3])),
                static_cast<uint8_t>((GetHexValueFromChar(colorStr[4]) << 4) + GetHexValueFromChar(colorStr[5]))
            );
        }

        static unsigned int GetHexValueFromChar(char const token)
        {
            if (token >= '0' && token <= '9')
            {
                return token - '0';
            }
            else if (token >= 'a' && token <= 'f')
            {
                char constexpr offset = static_cast<char>(10);
                return offset + (token - 'a');
            }

            return '\0';
        }

        template<typename T>
        static void AdvanceDigger(EDirection const direction, unsigned int const steps, VectorTool::Vector2<T>& diggerPosition)
        {
            switch (direction)
            {
            case EDirection::Up:    diggerPosition[0] -= steps; break;
            case EDirection::Down:  diggerPosition[0] += steps; break;
            case EDirection::Left:  diggerPosition[1] -= steps; break;
            case EDirection::Right: diggerPosition[1] += steps; break;
            default: break;
            }
        }

        static void Flood(GridTool::Grid<Color const*>& gridToFlood, Color const* floodColor, Vector2sz const floodPos)
        {
            if (gridToFlood.ReadAt(floodPos) != nullptr)
            {
                return;
            }

            gridToFlood.WriteAt(floodPos) = floodColor;

            Flood(gridToFlood, floodColor, Vector2sz(floodPos[0] - 1, floodPos[1]));
            Flood(gridToFlood, floodColor, Vector2sz(floodPos[0] + 1, floodPos[1]));
            Flood(gridToFlood, floodColor, Vector2sz(floodPos[0], floodPos[1] - 1));
            Flood(gridToFlood, floodColor, Vector2sz(floodPos[0], floodPos[1] + 1));
        }
    };
}
