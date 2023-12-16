#pragma once

#include <functional>
#include <vector>

namespace MatrixTool
{
    template <typename T>
    struct Matrix2D
    {
        std::vector<std::vector<T>> m_data;

        Matrix2D() {}
        Matrix2D(size_t const lineCount, size_t const columnCount) { Resize(lineCount, columnCount); }

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
    void ForEach(Matrix2D<T>& matrix, std::function<void(T&, size_t const, size_t const)> func)
    {
        for (size_t line = 0; line < matrix.GetLineCount(); ++line)
        {
            for (size_t column = 0; column < matrix.GetColumnCount(); ++column)
            {
                func(matrix.m_data[line][column], line, column);
            }
        }
    }

    template <typename T>
    void ForEach(Matrix2D<T> const& matrix, std::function<void(T const&, size_t const, size_t const)> func)
    {
        for (size_t line = 0; line < matrix.GetLineCount(); ++line)
        {
            for (size_t column = 0; column < matrix.GetColumnCount(); ++column)
            {
                func(matrix.m_data[line][column], line, column);
            }
        }
    }
}
