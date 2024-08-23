
#pragma once

#include <cmath>

namespace aoc::core
{
    #define EXPR_SQUARE(_expr) (_expr) * (_expr)

    template <typename T>
    struct Vector3
    {
        T m_data[3];

        Vector3() : m_data{ 0, 0, 0 } {}
        explicit Vector3(T const s) : m_data{ s, s, s } {}
        Vector3(T const x, T const y, T const z) : m_data{ x, y, z } {}
        Vector3(Vector3<T> const& other) : m_data{ other[0], other[1], other[2] } {}

        T const& operator[](size_t const index) const { return m_data[index]; }
        T& operator[](size_t const index) { return m_data[index]; }
        T const& operator()(size_t const index) const { return m_data[index]; }
        T& operator()(size_t const index) { return m_data[index]; }

        bool operator==(Vector3<T> const& rhs) const { return m_data[0] == rhs[0] && m_data[1] == rhs[1] && m_data[2] == rhs[2]; }
        bool operator!=(Vector3<T> const& rhs) const { return m_data[0] != rhs[0] || m_data[1] != rhs[1] || m_data[2] != rhs[2]; }
        bool operator<(Vector3<T> const& rhs) const { return m_data[0] == rhs[0] ? (m_data[1] == rhs[1] ? (m_data[2] < rhs[2]) : (m_data[1] < rhs[1])) : (m_data[0] < rhs[0]); }
        bool operator>(Vector3<T> const& rhs) const { return m_data[0] == rhs[0] ? (m_data[1] == rhs[1] ? (m_data[2] > rhs[2]) : (m_data[1] > rhs[1])) : (m_data[0] > rhs[0]); }

        Vector3<T>& operator+=(Vector3<T> const& rhs)
        {
            m_data[0] += rhs.m_data[0];
            m_data[1] += rhs.m_data[1];
            m_data[2] += rhs.m_data[2];
            return *this;
        }

        Vector3<T>& operator-=(Vector3<T> const& rhs)
        {
            m_data[0] -= rhs.m_data[0];
            m_data[1] -= rhs.m_data[1];
            m_data[2] -= rhs.m_data[2];
            return *this;
        }

        Vector3<T>& operator*=(Vector3<T> const& rhs)
        {
            m_data[0] *= rhs.m_data[0];
            m_data[1] *= rhs.m_data[1];
            m_data[2] *= rhs.m_data[2];
            return *this;
        }

        Vector3<T>& operator/=(Vector3<T> const& rhs)
        {
            m_data[0] /= rhs.m_data[0];
            m_data[1] /= rhs.m_data[1];
            m_data[2] /= rhs.m_data[2];
            return *this;
        }

        Vector3<T>& operator+=(T const scalar)
        {
            m_data[0] += scalar;
            m_data[1] += scalar;
            m_data[2] += scalar;
            return *this;
        }

        Vector3<T>& operator-=(T const scalar)
        {
            m_data[0] -= scalar;
            m_data[1] -= scalar;
            m_data[2] -= scalar;
            return *this;
        }

        Vector3<T>& operator*=(T const scalar)
        {
            m_data[0] *= scalar;
            m_data[1] *= scalar;
            m_data[2] *= scalar;
            return *this;
        }

        Vector3<T>& operator/=(T const scalar)
        {
            m_data[0] /= scalar;
            m_data[1] /= scalar;
            m_data[2] /= scalar;
            return *this;
        }

        Vector3<T> operator+(Vector3<T> const& rhs) const
        {
            return Vector3<T>(
                m_data[0] + rhs.m_data[0],
                m_data[1] + rhs.m_data[1],
                m_data[2] + rhs.m_data[2]);
        }

        Vector3<T> operator-(Vector3<T> const& rhs) const
        {
            return Vector3<T>(
                m_data[0] - rhs.m_data[0],
                m_data[1] - rhs.m_data[1],
                m_data[2] - rhs.m_data[2]);
        }

        Vector3<T> operator*(Vector3<T> const& rhs) const
        {
            return Vector3<T>(
                m_data[0] * rhs.m_data[0],
                m_data[1] * rhs.m_data[1],
                m_data[2] * rhs.m_data[2]);
        }

        Vector3<T> operator/(Vector3<T> const& rhs) const
        {
            return Vector3<T>(
                m_data[0] / rhs.m_data[0],
                m_data[1] / rhs.m_data[1],
                m_data[2] / rhs.m_data[2]);
        }

        Vector3<T> operator+(T const scalar) const
        {
            return Vector3<T>(
                m_data[0] + scalar,
                m_data[1] + scalar,
                m_data[2] + scalar);
        }

        Vector3<T> operator-(T const scalar) const
        {
            return Vector3<T>(
                m_data[0] - scalar,
                m_data[1] - scalar,
                m_data[2] - scalar);
        }

        Vector3<T> operator*(T const scalar) const
        {
            return Vector3<T>(
                m_data[0] * scalar,
                m_data[1] * scalar,
                m_data[2] * scalar);
        }

        Vector3<T> operator/(T const scalar) const
        {
            return Vector3<T>(
                m_data[0] / scalar,
                m_data[1] / scalar,
                m_data[2] / scalar);
        }

        static T DotProduct(Vector3<T> const& lhs, Vector3<T> const& rhs)
        {
            return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
        }

        static T MagnitudeSquared(Vector3<T> const& lhs)
        {
            return EXPR_SQUARE(lhs[0]) + EXPR_SQUARE(lhs[1]) + EXPR_SQUARE(lhs[2]);
        }

        static T Magnitude(Vector3<T> const& lhs)
        {
            return static_cast<T>(sqrt(EXPR_SQUARE(lhs[0]) + EXPR_SQUARE(lhs[1]) + EXPR_SQUARE(lhs[2])));
        }

        static T DistanceSquared(Vector3<T> const& lhs, Vector3<T> const& rhs)
        {
            return EXPR_SQUARE(lhs[0] - rhs[0]) + EXPR_SQUARE(lhs[1] - rhs[1]) + EXPR_SQUARE(lhs[2] - rhs[2]);
        }

        static T Distance(Vector3<T> const& lhs, Vector3<T> const& rhs)
        {
            return static_cast<T>(sqrt(EXPR_SQUARE(lhs[0] - rhs[0]) + EXPR_SQUARE(lhs[1] - rhs[1]) + EXPR_SQUARE(lhs[2] - rhs[2])));
        }

        static T ManhattanMagnitude(Vector3<T> const& lhs)
        {
            return abs(lhs[0]) + abs(lhs[1]) + abs(lhs[2]);
        }

        static T ManhattanDistance(Vector3<T> const& lhs, Vector3<T> const& rhs)
        {
            return abs(lhs[0] - rhs[0]) + abs(lhs[1] - rhs[1]) + abs(lhs[2] - rhs[2]);
        }
    };

    #undef EXPR_SQUARE
}
