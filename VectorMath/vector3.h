#ifndef TERRAIN_MESH_GENERATOR__VECTOR_MATH__VECTOR_3_DEF
#define TERRAIN_MESH_GENERATOR__VECTOR_MATH__VECTOR_3_DEF
#include <cmath>

/* A simple vector math library. Ideally we would use an existing one, but this
 * is just for fun and will save some build pain. If performance is insufficient,
 * using an external library is highly recommended.
 * 
 * This is currently implemented as a template class, in case we want to move to
 * 64 bit floating point values / etc and to support the maximum number of
 * engines and frameworks.
 */
namespace terrain_mesh_generator::vector_math
{
    template <typename T>
    class Vector3
    {
    public:
        Vector3<T>() : x(0), y(0), z(0) {}
        Vector3<T>(T x, T y, T z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        Vector3<T>(const Vector3<T> &other) = default;
        Vector3<T>(Vector3<T> &&other) = default;
        ~Vector3<T>() = default;

        static Vector3<T> zero()
        {
            return Vector3<T>(0, 0, 0);
        }

        static Vector3<T> one()
        {
            return Vector3<T>(1, 1, 1);
        }

        Vector3<T> operator=(const Vector3<T> &other)
        {
            return Vector3<T>(other);
        }

        bool operator==(const Vector3<T> &other) const
        {
            return x == other.x &&
                   y == other.y &&
                   z == other.z;
        }

        Vector3<T> operator+(const Vector3<T> &other) const
        {
            return Vector3<T>(x + other.x,
                              y + other.y,
                              z + other.z);
        }

        Vector3<T> &operator+=(const Vector3<T> &other)
        {
            *this = *this + other;
            return *this;
        }

        Vector3<T> operator-(const Vector3<T> &other) const
        {
            return Vector3<T>(x - other.x,
                              y - other.y,
                              z - other.z);
        }

        Vector3<T> &operator-=(const Vector3<T> &other)
        {
            *this = *this - other;
            return *this;
        }

        Vector3<T> operator-() const
        {
            return Vector3<T>(-x, -y, -z);
        }

        Vector3<T> operator*(const T &other) const
        {
            return Vector3<T>(x * other,
                              y * other,
                              z * other);
        }

        Vector3<T> operator*(const Vector3<T> &other) const
        {
            return Vector3<T>(y * other.z - z * other.y,
                              z * other.x - x * other.z,
                              x * other.y - y * other.x);
        }

        Vector3<T> operator*=(const T &other)
        {
            *this = *this * other;
            return *this;
        }

        Vector3<T> operator/(const T &other) const
        {
            return Vector3<T>(x / other,
                              y / other,
                              z / other);
        }

        Vector3<T> operator/=(const T &other)
        {
            *this = *this / other;
            return *this;
        }

        T Dot(const Vector3<T> &other) const
        {
            return x * other.x +
                   y * other.y +
                   z * other.z;
        }

        void normalize()
        {
            T m = magnitude();
            if (m)
            {
                *this /= m;
            }
        }

        T magnitude()
        {
            return sqrt(x * x + y * y + z * z);
        }

        T x, y, z;
    };
}
#endif