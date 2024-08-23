
#pragma once

#include <cmath>

namespace aoc::core
{
    #define EXPR_SQUARE(_expr) (_expr) * (_expr)

    template <typename T>
    struct Vector2
    {
        T m_data[2];

        Vector2() : m_data{ 0, 0 } {}
        explicit Vector2(T const s) : m_data{ s, s } {}
        Vector2(T const x, T const y) : m_data{ x, y } {}
        Vector2(Vector2<T> const& other) : m_data{ other[0], other[1] } {}

        T const& operator[](size_t const index) const { return m_data[index]; }
        T& operator[](size_t const index) { return m_data[index]; }
        T const& operator()(size_t const index) const { return m_data[index]; }
        T& operator()(size_t const index) { return m_data[index]; }

        bool operator==(Vector2<T> const& rhs) const { return m_data[0] == rhs[0] && m_data[1] == rhs[1]; }
        bool operator!=(Vector2<T> const& rhs) const { return m_data[0] != rhs[0] || m_data[1] != rhs[1]; }
        bool operator<(Vector2<T> const& rhs) const { return m_data[0] == rhs[0] ? (m_data[1] < rhs[1]) : (m_data[0] < rhs[0]); }
        bool operator>(Vector2<T> const& rhs) const { return m_data[0] == rhs[0] ? (m_data[1] > rhs[1]) : (m_data[0] > rhs[0]); }

        Vector2<T>& operator+=(Vector2<T> const& rhs)
        {
            m_data[0] += rhs.m_data[0];
            m_data[1] += rhs.m_data[1];
            return *this;
        }

        Vector2<T>& operator-=(Vector2<T> const& rhs)
        {
            m_data[0] -= rhs.m_data[0];
            m_data[1] -= rhs.m_data[1];
            return *this;
        }

        Vector2<T>& operator*=(Vector2<T> const& rhs)
        {
            m_data[0] *= rhs.m_data[0];
            m_data[1] *= rhs.m_data[1];
            return *this;
        }

        Vector2<T>& operator/=(Vector2<T> const& rhs)
        {
            m_data[0] /= rhs.m_data[0];
            m_data[1] /= rhs.m_data[1];
            return *this;
        }

        Vector2<T>& operator+=(T const scalar)
        {
            m_data[0] += scalar;
            m_data[1] += scalar;
            return *this;
        }

        Vector2<T>& operator-=(T const scalar)
        {
            m_data[0] -= scalar;
            m_data[1] -= scalar;
            return *this;
        }

        Vector2<T>& operator*=(T const scalar)
        {
            m_data[0] *= scalar;
            m_data[1] *= scalar;
            return *this;
        }

        Vector2<T>& operator/=(T const scalar)
        {
            m_data[0] /= scalar;
            m_data[1] /= scalar;
            return *this;
        }

        Vector2<T> operator+(Vector2<T> const& rhs) const
        {
            return Vector2<T>(
                m_data[0] + rhs.m_data[0],
                m_data[1] + rhs.m_data[1]);
        }

        Vector2<T> operator-(Vector2<T> const& rhs) const
        {
            return Vector2<T>(
                m_data[0] - rhs.m_data[0],
                m_data[1] - rhs.m_data[1]);
        }

        Vector2<T> operator*(Vector2<T> const& rhs) const
        {
            return Vector2<T>(
                m_data[0] * rhs.m_data[0],
                m_data[1] * rhs.m_data[1]);
        }

        Vector2<T> operator/(Vector2<T> const& rhs) const
        {
            return Vector2<T>(
                m_data[0] / rhs.m_data[0],
                m_data[1] / rhs.m_data[1]);
        }

        Vector2<T> operator+(T const scalar) const
        {
            return Vector2<T>(
                m_data[0] + scalar,
                m_data[1] + scalar);
        }

        Vector2<T> operator-(T const scalar) const
        {
            return Vector2<T>(
                m_data[0] - scalar,
                m_data[1] - scalar);
        }

        Vector2<T> operator*(T const scalar) const
        {
            return Vector2<T>(
                m_data[0] * scalar,
                m_data[1] * scalar);
        }

        Vector2<T> operator/(T const scalar) const
        {
            return Vector2<T>(
                m_data[0] / scalar,
                m_data[1] / scalar);
        }

        static T DotProduct(Vector2<T> const& lhs, Vector2<T> const& rhs)
        {
            return lhs[0] * rhs[0] + lhs[1] * rhs[1];
        }

        static T MagnitudeSqared(Vector2<T> const& lhs)
        {
            return EXPR_SQUARE(lhs[0]) + EXPR_SQUARE(lhs[1]);
        }

        static T Magnitude(Vector2<T> const& lhs)
        {
            return static_cast<T>(sqrt(EXPR_SQUARE(lhs[0]) + EXPR_SQUARE(lhs[1])));
        }

        static T DistanceSquared(Vector2<T> const& lhs, Vector2<T> const& rhs)
        {
            return EXPR_SQUARE(lhs[0] - rhs[0]) + EXPR_SQUARE(lhs[1] - rhs[1]);
        }

        static T Distance(Vector2<T> const& lhs, Vector2<T> const& rhs)
        {
            return static_cast<T>(sqrt(EXPR_SQUARE(lhs[0] - rhs[0]) + EXPR_SQUARE(lhs[1] - rhs[1])));
        }

        static T ManhattanMagnitude(Vector2<T> const& lhs)
        {
            return abs(lhs[0]) + abs(lhs[1]);
        }

        static T ManhattanDistance(Vector2<T> const& lhs, Vector2<T> const& rhs)
        {
            return abs(lhs[0] - rhs[0]) + abs(lhs[1] - rhs[1]);
        }
    };

    #undef EXPR_SQUARE
}