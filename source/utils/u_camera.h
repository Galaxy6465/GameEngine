#pragma once

#include <cmath>
#include <stdexcept>

namespace Utils {

constexpr float Pi = 3.14159265358979323846f;

inline float DegreesToRadians(float degrees)
{
    return degrees * (Pi / 180.0f);
}

inline float RadiansToDegrees(float radians)
{
    return radians * (180.0f / Pi);
}

struct Vec3 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct Mat4 {
    float elements[16]{};

    static Mat4 Identity()
    {
        Mat4 result{};
        result.elements[0] = 1.0f;
        result.elements[5] = 1.0f;
        result.elements[10] = 1.0f;
        result.elements[15] = 1.0f;
        return result;
    }

    static Mat4 Translation(const Vec3& translation)
    {
        Mat4 result = Identity();
        result.elements[12] = translation.x;
        result.elements[13] = translation.y;
        result.elements[14] = translation.z;
        return result;
    }

    static Mat4 Scale(const Vec3& scale)
    {
        Mat4 result{};
        result.elements[0] = scale.x;
        result.elements[5] = scale.y;
        result.elements[10] = scale.z;
        result.elements[15] = 1.0f;
        return result;
    }

    static Mat4 RotationX(float radians)
    {
        Mat4 result = Identity();
        const float cosine = std::cos(radians);
        const float sine = std::sin(radians);
        result.elements[5] = cosine;
        result.elements[6] = sine;
        result.elements[9] = -sine;
        result.elements[10] = cosine;
        return result;
    }

    static Mat4 RotationY(float radians)
    {
        Mat4 result = Identity();
        const float cosine = std::cos(radians);
        const float sine = std::sin(radians);
        result.elements[0] = cosine;
        result.elements[2] = -sine;
        result.elements[8] = sine;
        result.elements[10] = cosine;
        return result;
    }

    static Mat4 RotationZ(float radians)
    {
        Mat4 result = Identity();
        const float cosine = std::cos(radians);
        const float sine = std::sin(radians);
        result.elements[0] = cosine;
        result.elements[1] = sine;
        result.elements[4] = -sine;
        result.elements[5] = cosine;
        return result;
    }

    static Mat4 Perspective(float verticalFovRadians, float aspectRatio,
                            float nearPlane, float farPlane)
    {
        if (aspectRatio <= 0.0f || nearPlane <= 0.0f || farPlane <= nearPlane ||
            verticalFovRadians <= 0.0f || verticalFovRadians >= Pi) {
            throw std::invalid_argument("Invalid perspective projection parameters");
        }

        const float tangent = std::tan(verticalFovRadians * 0.5f);
        Mat4 result{};
        result.elements[0] = 1.0f / (aspectRatio * tangent);
        result.elements[5] = 1.0f / tangent;
        result.elements[10] = -(farPlane + nearPlane) / (farPlane - nearPlane);
        result.elements[11] = -1.0f;
        result.elements[14] = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);
        return result;
    }

    static Mat4 LookAt(const Vec3& position, const Vec3& target, const Vec3& up)
    {
        const Vec3 forward = Normalize(Subtract(target, position));
        const Vec3 right = Normalize(Cross(forward, up));
        const Vec3 correctedUp = Cross(right, forward);

        Mat4 result = Identity();
        result.elements[0] = right.x;
        result.elements[4] = right.y;
        result.elements[8] = right.z;
        result.elements[1] = correctedUp.x;
        result.elements[5] = correctedUp.y;
        result.elements[9] = correctedUp.z;
        result.elements[2] = -forward.x;
        result.elements[6] = -forward.y;
        result.elements[10] = -forward.z;
        result.elements[12] = -Dot(right, position);
        result.elements[13] = -Dot(correctedUp, position);
        result.elements[14] = Dot(forward, position);
        return result;
    }

    const float* Data() const
    {
        return elements;
    }

    Mat4 operator*(const Mat4& other) const
    {
        Mat4 result{};
        for (int column = 0; column < 4; ++column) {
            for (int row = 0; row < 4; ++row) {
                for (int index = 0; index < 4; ++index) {
                    result.elements[column * 4 + row] +=
                        elements[index * 4 + row] * other.elements[column * 4 + index];
                }
            }
        }
        return result;
    }

private:
    static Vec3 Subtract(const Vec3& left, const Vec3& right)
    {
        return {left.x - right.x, left.y - right.y, left.z - right.z};
    }

    static Vec3 Cross(const Vec3& left, const Vec3& right)
    {
        return {
            left.y * right.z - left.z * right.y,
            left.z * right.x - left.x * right.z,
            left.x * right.y - left.y * right.x
        };
    }

    static float Dot(const Vec3& left, const Vec3& right)
    {
        return left.x * right.x + left.y * right.y + left.z * right.z;
    }

    static Vec3 Normalize(const Vec3& vector)
    {
        const float length = std::sqrt(Dot(vector, vector));
        if (length <= 0.0f) {
            throw std::invalid_argument("Cannot normalize a zero-length camera vector");
        }
        return {vector.x / length, vector.y / length, vector.z / length};
    }
};

class Camera {
public:
    Camera(const Vec3& position = {2.0f, 2.0f, 3.0f},
           const Vec3& target = {0.0f, 0.0f, 0.0f},
           const Vec3& up = {0.0f, 1.0f, 0.0f},
           float verticalFovRadians = DegreesToRadians(45.0f),
           float aspectRatio = 4.0f / 3.0f,
           float nearPlane = 0.1f,
           float farPlane = 100.0f)
        : m_Position(position),
          m_Target(target),
          m_Up(up),
          m_VerticalFovRadians(verticalFovRadians),
          m_AspectRatio(aspectRatio),
          m_NearPlane(nearPlane),
          m_FarPlane(farPlane)
    {
    }

    void SetPosition(const Vec3& position) { m_Position = position; }
    void SetTarget(const Vec3& target) { m_Target = target; }
    void SetUp(const Vec3& up) { m_Up = up; }

    void SetPerspective(float verticalFovRadians, float aspectRatio,
                        float nearPlane, float farPlane)
    {
        m_VerticalFovRadians = verticalFovRadians;
        m_AspectRatio = aspectRatio;
        m_NearPlane = nearPlane;
        m_FarPlane = farPlane;
    }

    Mat4 GetViewMatrix() const
    {
        return Mat4::LookAt(m_Position, m_Target, m_Up);
    }

    Mat4 GetProjectionMatrix() const
    {
        return Mat4::Perspective(
            m_VerticalFovRadians, m_AspectRatio, m_NearPlane, m_FarPlane);
    }

private:
    Vec3 m_Position;
    Vec3 m_Target;
    Vec3 m_Up;
    float m_VerticalFovRadians;
    float m_AspectRatio;
    float m_NearPlane;
    float m_FarPlane;
};

} // namespace Utils
