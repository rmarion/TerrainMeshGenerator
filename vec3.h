#ifndef TERRAIN_MESH_GENERATOR__VEC_3_DEF
#define TERRAIN_MESH_GENERATOR__VEC_3_DEF

namespace terrain_mesh_generator
{
    template <typename T>
    struct vec3
    {
        T x;
        T y;
        T z;

        vec3(T x, T y, T z) : x(x), y(y), z(z) {}
    };
}

#endif