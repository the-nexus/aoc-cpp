#include "VectorTests.h"

#include "../tools/TestTool.h"
#include "../tools/VectorTool.h"

namespace Tests
{
    namespace Vector2
    {
#pragma region Constructors
        TEST_FUNC(ConstructorEmpty)
        {
            Vector2i const vec;
            return vec[0] == 0 && vec[1] == 0;
        }

        TEST_FUNC(ConstructorScalar)
        {
            Vector2i const vec(1);
            return vec[0] == 1 && vec[1] == 1;
        }

        TEST_FUNC(ConstructorComponents)
        {
            Vector2i const vec(1, 2);
            return vec[0] == 1 && vec[1] == 2;
        }

        TEST_FUNC(ConstructorCopy)
        {
            Vector2i left;
            Vector2i const right(1, 2);
            left = right;
            return left[0] == 1 && left[1] == 2;
        }
#pragma endregion

#pragma region Write Access
        TEST_FUNC(WriteAccessBracket)
        {
            Vector2i vec;
            vec[0] = 1;
            vec[1] = 2;
            return vec[0] == 1 && vec[1] == 2;
        }

        TEST_FUNC(WriteAccessParenthesis)
        {
            Vector2i vec;
            vec(0) = 1;
            vec(1) = 2;
            return vec(0) == 1 && vec(1) == 2;
        }
#pragma endregion

#pragma region Vector Operations (Self)
        TEST_FUNC(AddVectorSelf)
        {
            Vector2i left(1, 2);
            Vector2i const right(3, 4);
            left += right;
            return left[0] == 4 && left[1] == 6;
        }

        TEST_FUNC(SubtractVectorSelf)
        {
            Vector2i left(4, 3);
            Vector2i const right(1, 2);
            left -= right;
            return left[0] == 3 && left[1] == 1;
        }

        TEST_FUNC(MultiplyVectorSelf)
        {
            Vector2i left(2, 3);
            Vector2i const right(4, 5);
            left *= right;
            return left[0] == 8 && left[1] == 15;
        }

        TEST_FUNC(DivideVectorSelf)
        {
            Vector2i left(6, 8);
            Vector2i const right(3, 2);
            left /= right;
            return left[0] == 2 && left[1] == 4;
        }
#pragma endregion

#pragma region Scalar Operations (Self)
        TEST_FUNC(AddScalarSelf)
        {
            Vector2i left(1, 2);
            int const right = 3;
            left += right;
            return left[0] == 4 && left[1] == 5;
        }

        TEST_FUNC(SubtractScalarSelf)
        {
            Vector2i left(4, 3);
            int const right = 2;
            left -= right;
            return left[0] == 2 && left[1] == 1;
        }

        TEST_FUNC(MultiplyScalarSelf)
        {
            Vector2i left(2, 3);
            int const right = 4;
            left *= right;
            return left[0] == 8 && left[1] == 12;
        }

        TEST_FUNC(DivideScalarSelf)
        {
            Vector2i left(6, 8);
            int const right = 2;
            left /= right;
            return left[0] == 3 && left[1] == 4;
        }
#pragma endregion

#pragma region Vector Operations
        TEST_FUNC(AddVector)
        {
            Vector2i const left(1, 2);
            Vector2i const right(3, 4);
            Vector2i const vec = left + right;
            return vec[0] == 4 && vec[1] == 6;
        }

        TEST_FUNC(SubtractVector)
        {
            Vector2i const left(4, 3);
            Vector2i const right(1, 2);
            Vector2i const vec = left - right;
            return vec[0] == 3 && vec[1] == 1;
        }

        TEST_FUNC(MultiplyVector)
        {
            Vector2i const left(2, 3);
            Vector2i const right(4, 5);
            Vector2i const vec = left * right;
            return vec[0] == 8 && vec[1] == 15;
        }

        TEST_FUNC(DivideVector)
        {
            Vector2i const left(6, 8);
            Vector2i const right(3, 2);
            Vector2i const vec = left / right;
            return vec[0] == 2 && vec[1] == 4;
        }
#pragma endregion

#pragma region Scalar Operations
        TEST_FUNC(AddScalar)
        {
            Vector2i const left(1, 2);
            int const right = 3;
            Vector2i const vec = left + right;
            return vec[0] == 4 && vec[1] == 5;
        }

        TEST_FUNC(SubtractScalar)
        {
            Vector2i const left(4, 3);
            int const right = 2;
            Vector2i const vec = left - right;
            return vec[0] == 2 && vec[1] == 1;
        }

        TEST_FUNC(MultiplyScalar)
        {
            Vector2i const left(2, 3);
            int const right = 4;
            Vector2i const vec = left * right;
            return vec[0] == 8 && vec[1] == 12;
        }

        TEST_FUNC(DivideScalar)
        {
            Vector2i const left(6, 8);
            int const right = 2;
            Vector2i const vec = left / right;
            return vec[0] == 3 && vec[1] == 4;
        }
#pragma endregion

#pragma region Math
        TEST_FUNC(DotProduct)
        {
            Vector2i const left(1, 2);
            Vector2i const right(3, 4);
            int const result = Vector2i::DotProduct(left, right);
            return result == 11;
        }

        TEST_FUNC(MagnitudeSquared)
        {
            Vector2i const left(3, 4);
            int const result = Vector2i::MagnitudeSqared(left);
            return result == 25;
        }

        TEST_FUNC(Magnitude)
        {
            Vector2i const left(3, 4);
            int const result = Vector2i::Magnitude(left);
            return result == 5;
        }

        TEST_FUNC(DistanceSquared)
        {
            Vector2i const left(1, 6);
            Vector2i const right(4, 2);
            int const result = Vector2i::DistanceSquared(left, right);
            return result == 25;
        }

        TEST_FUNC(Distance)
        {
            Vector2i const left(1, 6);
            Vector2i const right(4, 2);
            int const result = Vector2i::Distance(left, right);
            return result == 5;
        }

        TEST_FUNC(ManhattanMagnitude)
        {
            Vector2i const left(3, 4);
            int const result = Vector2i::ManhattanMagnitude(left);
            return result == 7;
        }

        TEST_FUNC(ManhattanDistance)
        {
            Vector2i const left(1, 6);
            Vector2i const right(4, 2);
            int const result = Vector2i::ManhattanDistance(left, right);
            return result == 7;
        }
#pragma endregion

        void RunTests()
        {
            BEGIN_TEST_GROUP(Vector2);

            RUN_TEST_FUNC(ConstructorEmpty);
            RUN_TEST_FUNC(ConstructorScalar);
            RUN_TEST_FUNC(ConstructorComponents);

            RUN_TEST_FUNC(WriteAccessBracket);
            RUN_TEST_FUNC(WriteAccessParenthesis);

            RUN_TEST_FUNC(AddVectorSelf);
            RUN_TEST_FUNC(SubtractVectorSelf);
            RUN_TEST_FUNC(MultiplyVectorSelf);
            RUN_TEST_FUNC(DivideVectorSelf);

            RUN_TEST_FUNC(AddScalarSelf);
            RUN_TEST_FUNC(SubtractScalarSelf);
            RUN_TEST_FUNC(MultiplyScalarSelf);
            RUN_TEST_FUNC(DivideScalarSelf);

            RUN_TEST_FUNC(AddVector);
            RUN_TEST_FUNC(SubtractVector);
            RUN_TEST_FUNC(MultiplyVector);
            RUN_TEST_FUNC(DivideVector);

            RUN_TEST_FUNC(AddScalar);
            RUN_TEST_FUNC(SubtractScalar);
            RUN_TEST_FUNC(MultiplyScalar);
            RUN_TEST_FUNC(DivideScalar);

            RUN_TEST_FUNC(DotProduct);
            RUN_TEST_FUNC(MagnitudeSquared);
            RUN_TEST_FUNC(Magnitude);
            RUN_TEST_FUNC(DistanceSquared);
            RUN_TEST_FUNC(Distance);
            RUN_TEST_FUNC(ManhattanMagnitude);
            RUN_TEST_FUNC(ManhattanDistance);

            END_TEST_GROUP();
        }
    }

    namespace Vector3
    {
#pragma region Constructors
        TEST_FUNC(ConstructorEmpty)
        {
            Vector3i const vec;
            return vec[0] == 0 && vec[1] == 0 && vec[2] == 0;
        }

        TEST_FUNC(ConstructorScalar)
        {
            Vector3i const vec(1);
            return vec[0] == 1 && vec[1] == 1 && vec[2] == 1;
        }

        TEST_FUNC(ConstructorComponents)
        {
            Vector3i const vec(1, 2, 3);
            return vec[0] == 1 && vec[1] == 2 && vec[2] == 3;
        }

        TEST_FUNC(ConstructorCopy)
        {
            Vector3i left;
            Vector3i const right(1, 2, 3);
            left = right;
            return left[0] == 1 && left[1] == 2 && left[2] == 3;
        }
#pragma endregion

#pragma region Write Access
        TEST_FUNC(WriteAccessBracket)
        {
            Vector3i vec;
            vec[0] = 1;
            vec[1] = 2;
            vec[2] = 3;
            return vec[0] == 1 && vec[1] == 2 && vec[2] == 3;
        }

        TEST_FUNC(WriteAccessParenthesis)
        {
            Vector3i vec;
            vec(0) = 1;
            vec(1) = 2;
            vec(2) = 3;
            return vec(0) == 1 && vec(1) == 2 && vec(2) == 3;
        }
#pragma endregion

#pragma region Vector Operations (Self)
        TEST_FUNC(AddVectorSelf)
        {
            Vector3i left(1, 2, 10);
            Vector3i const right(3, 4, 15);
            left += right;
            return left[0] == 4 && left[1] == 6 && left[2] == 25;
        }

        TEST_FUNC(SubtractVectorSelf)
        {
            Vector3i left(4, 3, 15);
            Vector3i const right(1, 2, 10);
            left -= right;
            return left[0] == 3 && left[1] == 1 && left[2] == 5;
        }

        TEST_FUNC(MultiplyVectorSelf)
        {
            Vector3i left(2, 3, 10);
            Vector3i const right(4, 5, 15);
            left *= right;
            return left[0] == 8 && left[1] == 15 && left[2] == 150;
        }

        TEST_FUNC(DivideVectorSelf)
        {
            Vector3i left(6, 8, 50);
            Vector3i const right(3, 2, 10);
            left /= right;
            return left[0] == 2 && left[1] == 4 && left[2] == 5;
        }
#pragma endregion

#pragma region Scalar Operations (Self)
        TEST_FUNC(AddScalarSelf)
        {
            Vector3i left(1, 2, 10);
            int const right = 3;
            left += right;
            return left[0] == 4 && left[1] == 5 && left[2] == 13;
        }

        TEST_FUNC(SubtractScalarSelf)
        {
            Vector3i left(4, 3, 10);
            int const right = 2;
            left -= right;
            return left[0] == 2 && left[1] == 1 && left[2] == 8;
        }

        TEST_FUNC(MultiplyScalarSelf)
        {
            Vector3i left(2, 3, 10);
            int const right = 4;
            left *= right;
            return left[0] == 8 && left[1] == 12 && left[2] == 40;
        }

        TEST_FUNC(DivideScalarSelf)
        {
            Vector3i left(6, 8, 10);
            int const right = 2;
            left /= right;
            return left[0] == 3 && left[1] == 4 && left[2] == 5;
        }
#pragma endregion

#pragma region Vector Operations
        TEST_FUNC(AddVector)
        {
            Vector3i const left(1, 2, 10);
            Vector3i const right(3, 4, 15);
            Vector3i const vec = left + right;
            return vec[0] == 4 && vec[1] == 6 && vec[2] == 25;
        }

        TEST_FUNC(SubtractVector)
        {
            Vector3i const left(4, 3, 15);
            Vector3i const right(1, 2, 10);
            Vector3i const vec = left - right;
            return vec[0] == 3 && vec[1] == 1 && vec[2] == 5;
        }

        TEST_FUNC(MultiplyVector)
        {
            Vector3i const left(2, 3, 10);
            Vector3i const right(4, 5, 15);
            Vector3i const vec = left * right;
            return vec[0] == 8 && vec[1] == 15 && vec[2] == 150;
        }

        TEST_FUNC(DivideVector)
        {
            Vector3i const left(6, 8, 50);
            Vector3i const right(3, 2, 10);
            Vector3i const vec = left / right;
            return vec[0] == 2 && vec[1] == 4 && vec[2] == 5;
        }
#pragma endregion

#pragma region Scalar Operations
        TEST_FUNC(AddScalar)
        {
            Vector3i const left(1, 2, 10);
            int const right = 3;
            Vector3i const vec = left + right;
            return vec[0] == 4 && vec[1] == 5 && vec[2] == 13;
        }

        TEST_FUNC(SubtractScalar)
        {
            Vector3i const left(4, 3, 10);
            int const right = 2;
            Vector3i const vec = left - right;
            return vec[0] == 2 && vec[1] == 1 && vec[2] == 8;
        }

        TEST_FUNC(MultiplyScalar)
        {
            Vector3i const left(2, 3, 10);
            int const right = 4;
            Vector3i const vec = left * right;
            return vec[0] == 8 && vec[1] == 12 && vec[2] == 40;
        }

        TEST_FUNC(DivideScalar)
        {
            Vector3i const left(6, 8, 10);
            int const right = 2;
            Vector3i const vec = left / right;
            return vec[0] == 3 && vec[1] == 4 && vec[2] == 5;
        }
#pragma endregion

#pragma region Math
        TEST_FUNC(DotProduct)
        {
            Vector3i const left(1, 2, 5);
            Vector3i const right(3, 4, 6);
            int const result = Vector3i::DotProduct(left, right);
            return result == 41;
        }

        TEST_FUNC(MagnitudeSquared)
        {
            Vector3i const left(3, 4, 5);
            int const result = Vector3i::MagnitudeSquared(left);
            return result == 50; // 7.07... casted to integer
        }

        TEST_FUNC(Magnitude)
        {
            Vector3i const left(3, 4, 5);
            int const result = Vector3i::Magnitude(left);
            return result == 7; // 7.07... casted to integer
        }

        TEST_FUNC(DistanceSquared)
        {
            Vector3i const left(1, 6, 3);
            Vector3i const right(4, 2, 8);
            int const result = Vector3i::DistanceSquared(left, right);
            return result == 50;
        }

        TEST_FUNC(Distance)
        {
            Vector3i const left(1, 6, 3);
            Vector3i const right(4, 2, 8);
            int const result = Vector3i::Distance(left, right);
            return result == 7; // 7.07... casted to integer
        }

        TEST_FUNC(ManhattanMagnitude)
        {
            Vector3i const left(3, 4, 5);
            int const result = Vector3i::ManhattanMagnitude(left);
            return result == 12;
        }

        TEST_FUNC(ManhattanDistance)
        {
            Vector3i const left(1, 6, 3);
            Vector3i const right(4, 2, 8);
            int const result = Vector3i::ManhattanDistance(left, right);
            return result == 12;
        }
#pragma endregion

        void RunTests()
        {
            BEGIN_TEST_GROUP(Vector3);

            RUN_TEST_FUNC(ConstructorEmpty);
            RUN_TEST_FUNC(ConstructorScalar);
            RUN_TEST_FUNC(ConstructorComponents);
            RUN_TEST_FUNC(ConstructorCopy);

            RUN_TEST_FUNC(WriteAccessBracket);
            RUN_TEST_FUNC(WriteAccessParenthesis);

            RUN_TEST_FUNC(AddVectorSelf);
            RUN_TEST_FUNC(SubtractVectorSelf);
            RUN_TEST_FUNC(MultiplyVectorSelf);
            RUN_TEST_FUNC(DivideVectorSelf);

            RUN_TEST_FUNC(AddScalarSelf);
            RUN_TEST_FUNC(SubtractScalarSelf);
            RUN_TEST_FUNC(MultiplyScalarSelf);
            RUN_TEST_FUNC(DivideScalarSelf);

            RUN_TEST_FUNC(AddVector);
            RUN_TEST_FUNC(SubtractVector);
            RUN_TEST_FUNC(MultiplyVector);
            RUN_TEST_FUNC(DivideVector);

            RUN_TEST_FUNC(AddScalar);
            RUN_TEST_FUNC(SubtractScalar);
            RUN_TEST_FUNC(MultiplyScalar);
            RUN_TEST_FUNC(DivideScalar);

            RUN_TEST_FUNC(DotProduct);
            RUN_TEST_FUNC(MagnitudeSquared);
            RUN_TEST_FUNC(Magnitude);
            RUN_TEST_FUNC(DistanceSquared);
            RUN_TEST_FUNC(Distance);
            RUN_TEST_FUNC(ManhattanMagnitude);
            RUN_TEST_FUNC(ManhattanDistance);

            END_TEST_GROUP();
        }
    }
}
