#pragma once

#include <functional>
#include <vector>
#include "VectorTool.h"

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
        inline Vector2sz GetDimensions() const { return Vector2sz(GetLineCount(), GetColumnCount()); }

        inline const T& ReadAt(Vector2sz const& position) const { return m_data[position[0]][position[1]]; }
        inline const T& ReadAt(size_t const line, size_t const column) const { return m_data[line][column]; }

        inline T& WriteAt(Vector2sz const& position) { return m_data[position[0]][position[1]]; }
        inline T& WriteAt(size_t const x, size_t const y) { return m_data[line][column]; }

        inline void Resize(Vector2sz const& dimensions) { Resize(dimensions[0], dimensions[1]); }
        void Resize(size_t const lineCount, size_t const columnCount)
        {
            m_data.resize(lineCount);
            for (size_t line = 0; line < lineCount; ++line)
            {
                m_data[line].resize(columnCount);
            }
        }

        void ForEach(std::function<void(T&, size_t const, size_t const)> func)
        {
            size_t const lineCount = GetLineCount();
            for (size_t line = 0; line < lineCount; ++line)
            {
                size_t const columnCount = GetColumnCount();
                for (size_t column = 0; column < columnCount; ++column)
                {
                    func(m_data[line][column], line, column);
                }
            }
        }

        void ForEach(std::function<void(T const&, size_t const, size_t const)> func) const
        {
            size_t const lineCount = GetLineCount();
            for (size_t line = 0; line < lineCount; ++line)
            {
                size_t const columnCount = GetColumnCount();
                for (size_t column = 0; column < columnCount(); ++column)
                {
                    func(m_data[line][column], line, column);
                }
            }
        }

        void SetAll(const T& itemData)
        {
            ForEach([&itemData](T& item, size_t const line, size_t const column)
                {
                    item = itemData;
                });
        }
    };
}
