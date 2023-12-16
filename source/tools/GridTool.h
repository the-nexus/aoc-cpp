#pragma once

#include <functional>
#include <vector>

namespace GridTool
{
    template <typename T>
    struct Grid
    {
        std::vector<std::vector<T>> m_data;

        Grid() {}
        Grid(size_t const lineCount, size_t const columnCount) { Resize(lineCount, columnCount); }

        inline size_t GetLineCount() const { return m_data.size(); }
        inline size_t GetColumnCount() const { return m_data.size() > 0 ? m_data[0].size() : 0; }

        inline const T& GetAt(size_t const x, size_t const y) const { return m_data[x][y]; }
        inline T GetAt(size_t const x, size_t const y) { return m_data[x][y]; }

        void Resize(size_t const lineCount, size_t const columnCount)
        {
            m_data.resize(lineCount);
            for (size_t line = 0; line < lineCount; ++line)
            {
                m_data[line].resize(columnCount);
            }
        }
    };

    template <typename T>
    void ForEach(Grid<T>& grid, std::function<void(T&, size_t const, size_t const)> func)
    {
        for (size_t line = 0; line < grid.GetLineCount(); ++line)
        {
            for (size_t column = 0; column < grid.GetColumnCount(); ++column)
            {
                func(grid.m_data[line][column], line, column);
            }
        }
    }

    template <typename T>
    void ForEach(Grid<T> const& grid, std::function<void(T const&, size_t const, size_t const)> func)
    {
        for (size_t line = 0; line < grid.GetLineCount(); ++line)
        {
            for (size_t column = 0; column < grid.GetColumnCount(); ++column)
            {
                func(grid.m_data[line][column], line, column);
            }
        }
    }
}
