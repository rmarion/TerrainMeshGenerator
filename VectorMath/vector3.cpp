#include "vector3.h"

namespace terrain_mesh_generator::vector_math
{
    Vector3::Vector3() : x(0), y(0), z(0) {}
    Vector3::Vector3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3 Vector3::zero()
    {
        return Vector3(0, 0, 0);
    }

    Vector3 Vector3::one()
    {
        return Vector3(1, 1, 1);
    }

    Vector3 Vector3::operator=(const Vector3 &other)
    {
        return Vector3(other);
    }

    bool Vector3::operator==(const Vector3 &other) const
    {
        return x == other.x &&
               y == other.y &&
               z == other.z;
    }

    Vector3 Vector3::operator+(const Vector3 &other) const
    {
        return Vector3(x + other.x,
                       y + other.y,
                       z + other.z);
    }

    Vector3 &Vector3::operator+=(const Vector3 &other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    Vector3 Vector3::operator-(const Vector3 &other) const
    {
        return Vector3(x - other.x,
                       y - other.y,
                       z - other.z);
    }

    Vector3 &Vector3::operator-=(const Vector3 &other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;

        return *this;
    }

    Vector3 Vector3::operator-() const
    {
        return Vector3(-x, -y, -z);
    }

    Vector3 Vector3::operator*(const float &other) const
    {
        return Vector3(x * other,
                       y * other,
                       z * other);
    }

    Vector3 Vector3::operator*(const Vector3 &other) const
    {
        return Vector3(y * other.z - z * other.y,
                       z * other.x - x * other.z,
                       x * other.y - y * other.x);
    }

    Vector3 Vector3::operator*=(const float &other)
    {
        *this = *this * other;
        return *this;
    }

    Vector3 Vector3::operator/(const float &other) const
    {
        return Vector3(x / other,
                       y / other,
                       z / other);
    }

    Vector3 Vector3::operator/=(const float &other)
    {
        *this = *this / other;
        return *this;
    }

    float Vector3::Dot(const Vector3 &other) const
    {
        return x * other.x +
               y * other.y +
               z * other.z;
    }

    void Vector3::normalize()
    {
        float m = magnitude();
        if (m)
        {
            *this /= m;
        }
    }

    float Vector3::magnitude()
    {
        return sqrt(x * x + y * y + z * z);
    }
}