#ifndef floatERRAIN_MESH_GENERAfloatOR__floatERRAIN_MESH_DEF
#define floatERRAIN_MESH_GENERAfloatOR__floatERRAIN_MESH_DEF

#include <cmath>
#include <stdexcept>
#include <vector>
#include "../VectorMath/vector3.h"
#include "../vec2.h"

namespace terrain_mesh_generator::terrain_mesh
{
    using std::vector;
    using vector_math::Vector3;

    class TerrainMesh
    {
    public:
        TerrainMesh(vector<float> heights, float spacing);

        int width_;
        vector<Vector3> vertices_;
        vector<int> triangles_;
        vector<Vector3> normals_;
        vector<vec2<float>> uv0_;
        vector<vec2<float>> uv1_;
        vector<vec2<float>> uv2_;
        vector<vec2<float>> uv3_;
        vector<Vector3> tangents_;

    private:
        static int GetVertIndex(int column, int row, int rowSize);
        static vector<Vector3> GetVertices(int numVerts, int width, float spacing, vector<float> heights);
        static vector<Vector3> GetNormals(vector<Vector3> vertices, int width);
        static vector<int> GetTriangles(int width);
        static vector<vec2<float>> GetUvs(float width);
    };
}

#endif
