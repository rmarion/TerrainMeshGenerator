#ifndef TERRAIN_MESH_GENERATOR__TERRAIN_MESH_DEF
#define TERRAIN_MESH_GENERATOR__TERRAIN_MESH_DEF

#include <vector>
#include "vec3.h"
#include "vec2.h"

namespace terrain_mesh_generator
{
    using std::vector;

    template <typename T>
    class TerrainMesh
    {
    public:
        TerrainMesh(vector<T> heights, T spacing);

        int width_;
        vector<vec3<T>> vertices_;
        vector<int> triangles_;
        vector<vec3<T>> normals_;
        vector<vec2<T>> uv0_;
        vector<vec2<T>> uv1_;
        vector<vec2<T>> uv2_;
        vector<vec2<T>> uv3_;
        vector<vec3<T>> tangents_;
    };
}

#endif
