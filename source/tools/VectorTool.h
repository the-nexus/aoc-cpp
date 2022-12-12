#pragma once

#include <cmath>

namespace VectorTool
{
    #define EXPR_SQUARE(_expr) (_expr) * (_expr)

    template <typename T>
    struct Vector2
    {
        T m_values[2];

        Vector2() : m_values{ 0, 0 } {}
        explicit Vector2(T const s) : m_values{ s, s } {}
        Vector2(T const x, T const y) : m_values{ x, y } {}
        Vector2(Vector2<T> const& other) : m_values{ other[0], other[1] } {}

        inline T const& operator[](size_t const index) const { return m_values[index]; }
        inline T& operator[](size_t const index) { return m_values[index]; }
        inline T const& operator()(size_t const index) const { return m_values[index]; }
        inline T& operator()(size_t const index) { return m_values[index]; }

        inline bool operator==(Vector2<T> const& rhs) const { return m_values[0] == rhs[0] && m_values[1] == rhs[1]; }
        inline bool operator!=(Vector2<T> const& rhs) const { return m_values[0] != rhs[0] || m_values[1] != rhs[1]; }
        inline bool operator<(Vector2<T> const& rhs) const { return m_values[0] == rhs[0] ? (m_values[1] < rhs[1]) : (m_values[0] < rhs[0]); }
        inline bool operator>(Vector2<T> const& rhs) const { return m_values[0] == rhs[0] ? (m_values[1] > rhs[1]) : (m_values[0] > rhs[0]); }

        Vector2<T>& operator+=(Vector2<T> const& rhs)
        {
            m_values[0] += rhs.m_values[0];
            m_values[1] += rhs.m_values[1];
            return *this;
        }

        Vector2<T>& operator-=(Vector2<T> const& rhs)
        {
            m_values[0] -= rhs.m_values[0];
            m_values[1] -= rhs.m_values[1];
            return *this;
        }

        Vector2<T>& operator*=(Vector2<T> const& rhs)
        {
            m_values[0] *= rhs.m_values[0];
            m_values[1] *= rhs.m_values[1];
            return *this;
        }

        Vector2<T>& operator/=(Vector2<T> const& rhs)
        {
            m_values[0] /= rhs.m_values[0];
            m_values[1] /= rhs.m_values[1];
            return *this;
        }

        Vector2<T>& operator+=(T const scalar)
        {
            m_values[0] += scalar;
            m_values[1] += scalar;
            return *this;
        }

        Vector2<T>& operator-=(T const scalar)
        {
            m_values[0] -= scalar;
            m_values[1] -= scalar;
            return *this;
        }

        Vector2<T>& operator*=(T const scalar)
        {
            m_values[0] *= scalar;
            m_values[1] *= scalar;
            return *this;
        }

        Vector2<T>& operator/=(T const scalar)
        {
            m_values[0] /= scalar;
            m_values[1] /= scalar;
            return *this;
        }

        Vector2<T> operator+(Vector2<T> const& rhs) const
        {
            return Vector2<T>(
                m_values[0] + rhs.m_values[0],
                m_values[1] + rhs.m_values[1]);
        }

        Vector2<T> operator-(Vector2<T> const& rhs) const
        {
            return Vector2<T>(
                m_values[0] - rhs.m_values[0],
                m_values[1] - rhs.m_values[1]);
        }

        Vector2<T> operator*(Vector2<T> const& rhs) const
        {
            return Vector2<T>(
                m_values[0] * rhs.m_values[0],
                m_values[1] * rhs.m_values[1]);
        }

        Vector2<T> operator/(Vector2<T> const& rhs) const
        {
            return Vector2<T>(
                m_values[0] / rhs.m_values[0],
                m_values[1] / rhs.m_values[1]);
        }

        Vector2<T> operator+(T const scalar) const
        {
            return Vector2<T>(
                m_values[0] + scalar,
                m_values[1] + scalar);
        }

        Vector2<T> operator-(T const scalar) const
        {
            return Vector2<T>(
                m_values[0] - scalar,
                m_values[1] - scalar);
        }

        Vector2<T> operator*(T const scalar) const
        {
            return Vector2<T>(
                m_values[0] * scalar,
                m_values[1] * scalar);
        }

        Vector2<T> operator/(T const scalar) const
        {
            return Vector2<T>(
                m_values[0] / scalar,
                m_values[1] / scalar);
        }

        inline static T DotProduct(Vector2<T> const& lhs, Vector2<T> const& rhs)
        {
            return lhs[0] * rhs[0] + lhs[1] * rhs[1];
        }

        inline static T MagnitudeSqared(Vector2<T> const& lhs)
        {
            return EXPR_SQUARE(lhs[0]) + EXPR_SQUARE(lhs[1]);
        }

        inline static T Magnitude(Vector2<T> const& lhs)
        {
            return static_cast<T>(sqrt(EXPR_SQUARE(lhs[0]) + EXPR_SQUARE(lhs[1])));
        }

        inline static T DistanceSquared(Vector2<T> const& lhs, Vector2<T> const& rhs)
        {
            return EXPR_SQUARE(lhs[0] - rhs[0]) + EXPR_SQUARE(lhs[1] - rhs[1]);
        }

        inline static T Distance(Vector2<T> const& lhs, Vector2<T> const& rhs)
        {
            return static_cast<T>(sqrt(EXPR_SQUARE(lhs[0] - rhs[0]) + EXPR_SQUARE(lhs[1] - rhs[1])));
        }

        inline static T ManhattanMagnitude(Vector2<T> const& lhs)
        {
            return abs(lhs[0]) + abs(lhs[1]);
        }

        inline static T ManhattanDistance(Vector2<T> const& lhs, Vector2<T> const& rhs)
        {
            return abs(lhs[0] - rhs[0]) + abs(lhs[1] - rhs[1]);
        }
    };

    template <typename T>
    struct Vector3
    {
        T m_values[3];

        Vector3() : m_values{ 0, 0, 0 } {}
        explicit Vector3(T const s) : m_values{ s, s, s } {}
        Vector3(T const x, T const y, T const z) : m_values{ x, y, z } {}
        Vector3(Vector3<T> const& other) : m_values{ other[0], other[1], other[2] } {}

        inline T const& operator[](size_t const index) const { return m_values[index]; }
        inline T& operator[](size_t const index) { return m_values[index]; }
        inline T const& operator()(size_t const index) const { return m_values[index]; }
        inline T& operator()(size_t const index) { return m_values[index]; }

        inline bool operator==(Vector3<T> const& rhs) const { return m_values[0] == rhs[0] && m_values[1] == rhs[1] && m_values[2] == rhs[2]; }
        inline bool operator!=(Vector3<T> const& rhs) const { return m_values[0] != rhs[0] || m_values[1] != rhs[1] || m_values[2] != rhs[2]; }
        inline bool operator<(Vector3<T> const& rhs) const { return m_values[0] == rhs[0] ? (m_values[1] == rhs[1] ? (m_values[2] < rhs[2]) : (m_values[1] < rhs[1])) : (m_values[0] < rhs[0]); }
        inline bool operator>(Vector3<T> const& rhs) const { return m_values[0] == rhs[0] ? (m_values[1] == rhs[1] ? (m_values[2] > rhs[2]) : (m_values[1] > rhs[1])) : (m_values[0] > rhs[0]); }

        Vector3<T>& operator+=(Vector3<T> const& rhs)
        {
            m_values[0] += rhs.m_values[0];
            m_values[1] += rhs.m_values[1];
            m_values[2] += rhs.m_values[2];
            return *this;
        }

        Vector3<T>& operator-=(Vector3<T> const& rhs)
        {
            m_values[0] -= rhs.m_values[0];
            m_values[1] -= rhs.m_values[1];
            m_values[2] -= rhs.m_values[2];
            return *this;
        }

        Vector3<T>& operator*=(Vector3<T> const& rhs)
        {
            m_values[0] *= rhs.m_values[0];
            m_values[1] *= rhs.m_values[1];
            m_values[2] *= rhs.m_values[2];
            return *this;
        }

        Vector3<T>& operator/=(Vector3<T> const& rhs)
        {
            m_values[0] /= rhs.m_values[0];
            m_values[1] /= rhs.m_values[1];
            m_values[2] /= rhs.m_values[2];
            return *this;
        }

        Vector3<T>& operator+=(T const scalar)
        {
            m_values[0] += scalar;
            m_values[1] += scalar;
            m_values[2] += scalar;
            return *this;
        }

        Vector3<T>& operator-=(T const scalar)
        {
            m_values[0] -= scalar;
            m_values[1] -= scalar;
            m_values[2] -= scalar;
            return *this;
        }

        Vector3<T>& operator*=(T const scalar)
        {
            m_values[0] *= scalar;
            m_values[1] *= scalar;
            m_values[2] *= scalar;
            return *this;
        }

        Vector3<T>& operator/=(T const scalar)
        {
            m_values[0] /= scalar;
            m_values[1] /= scalar;
            m_values[2] /= scalar;
            return *this;
        }

        Vector3<T> operator+(Vector3<T> const& rhs) const
        {
            return Vector3<T>(
                m_values[0] + rhs.m_values[0],
                m_values[1] + rhs.m_values[1],
                m_values[2] + rhs.m_values[2]);
        }

        Vector3<T> operator-(Vector3<T> const& rhs) const
        {
            return Vector3<T>(
                m_values[0] - rhs.m_values[0],
                m_values[1] - rhs.m_values[1],
                m_values[2] - rhs.m_values[2]);
        }

        Vector3<T> operator*(Vector3<T> const& rhs) const
        {
            return Vector3<T>(
                m_values[0] * rhs.m_values[0],
                m_values[1] * rhs.m_values[1],
                m_values[2] * rhs.m_values[2]);
        }

        Vector3<T> operator/(Vector3<T> const& rhs) const
        {
            return Vector3<T>(
                m_values[0] / rhs.m_values[0],
                m_values[1] / rhs.m_values[1],
                m_values[2] / rhs.m_values[2]);
        }

        Vector3<T> operator+(T const scalar) const
        {
            return Vector3<T>(
                m_values[0] + scalar,
                m_values[1] + scalar,
                m_values[2] + scalar);
        }

        Vector3<T> operator-(T const scalar) const
        {
            return Vector3<T>(
                m_values[0] - scalar,
                m_values[1] - scalar,
                m_values[2] - scalar);
        }

        Vector3<T> operator*(T const scalar) const
        {
            return Vector3<T>(
                m_values[0] * scalar,
                m_values[1] * scalar,
                m_values[2] * scalar);
        }

        Vector3<T> operator/(T const scalar) const
        {
            return Vector3<T>(
                m_values[0] / scalar,
                m_values[1] / scalar,
                m_values[2] / scalar);
        }

        inline static T DotProduct(Vector3<T> const& lhs, Vector3<T> const& rhs)
        {
            return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
        }

        inline static T MagnitudeSquared(Vector3<T> const& lhs)
        {
            return EXPR_SQUARE(lhs[0]) + EXPR_SQUARE(lhs[1]) + EXPR_SQUARE(lhs[2]);
        }

        inline static T Magnitude(Vector3<T> const& lhs)
        {
            return static_cast<T>(sqrt(EXPR_SQUARE(lhs[0]) + EXPR_SQUARE(lhs[1]) + EXPR_SQUARE(lhs[2])));
        }

        inline static T DistanceSquared(Vector3<T> const& lhs, Vector3<T> const& rhs)
        {
            return EXPR_SQUARE(lhs[0] - rhs[0]) + EXPR_SQUARE(lhs[1] - rhs[1]) + EXPR_SQUARE(lhs[2] - rhs[2]);
        }

        inline static T Distance(Vector3<T> const& lhs, Vector3<T> const& rhs)
        {
            return static_cast<T>(sqrt(EXPR_SQUARE(lhs[0] - rhs[0]) + EXPR_SQUARE(lhs[1] - rhs[1]) + EXPR_SQUARE(lhs[2] - rhs[2])));
        }

        inline static T ManhattanMagnitude(Vector3<T> const& lhs)
        {
            return abs(lhs[0]) + abs(lhs[1]) + abs(lhs[2]);
        }

        inline static T ManhattanDistance(Vector3<T> const& lhs, Vector3<T> const& rhs)
        {
            return abs(lhs[0] - rhs[0]) + abs(lhs[1] - rhs[1]) + abs(lhs[2] - rhs[2]);
        }
    };
}

typedef VectorTool::Vector2<int> Vector2i;
typedef VectorTool::Vector3<int> Vector3i;
typedef VectorTool::Vector2<unsigned int> Vector2u;
typedef VectorTool::Vector3<unsigned int> Vector3u;
typedef VectorTool::Vector2<float> Vector2f;
typedef VectorTool::Vector3<float> Vector3f;
typedef VectorTool::Vector2<double> Vector2d;
typedef VectorTool::Vector3<double> Vector3d;
