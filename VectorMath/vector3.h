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
    class Vector3
    {
    public:
        Vector3();
        Vector3(float x, float y, float z);
        Vector3(const Vector3 &other) = default;
        Vector3(Vector3 &&other) = default;
        ~Vector3() = default;

        static Vector3 zero();
        static Vector3 one();

        Vector3 operator=(const Vector3 &other);
        bool operator==(const Vector3 &other) const;
        Vector3 operator+(const Vector3 &other) const;
        Vector3 &operator+=(const Vector3 &other);
        Vector3 operator-(const Vector3 &other) const;
        Vector3 &operator-=(const Vector3 &other);
        Vector3 operator-() const;
        Vector3 operator*(const float &other) const;
        Vector3 operator*(const Vector3 &other) const;
        Vector3 operator*=(const float &other);
        Vector3 operator/(const float &other) const;
        Vector3 operator/=(const float &other);

        float Dot(const Vector3 &other) const;
        void normalize();
        float magnitude();

        float x, y, z;
    };
}
#endif