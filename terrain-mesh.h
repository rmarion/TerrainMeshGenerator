#ifndef TERRAIN_MESH_GENERATOR__TERRAIN_MESH_DEF
#define TERRAIN_MESH_GENERATOR__TERRAIN_MESH_DEF

#include <cmath>
#include <stdexcept>
#include <vector>
#include "VectorMath/vector3.h"
#include "vec2.h"

namespace terrain_mesh_generator
{
    using std::vector;
    using vector_math::Vector3;

    template <typename T>
    class TerrainMesh
    {
    public:
        TerrainMesh(vector<T> heights, T spacing)
        {
            // Terrain meshes will always be square
            width_ = sqrt(heights.size());
            if (heights.size() / (double)width_ != (double)width_)
            {
                throw std::invalid_argument("Heightmap must be square!");
            }

            int numVerts = width_ * width_;

            // It's possible to have these all in a single loop, but the benefits are trivial
            // and it would cause a large hit to readability.

            vertices_ = GetVertices(numVerts, width_, spacing, heights);

            // Normals

            // Triangles

            triangles_.reserve((width_ - 1) * (width_ - 1));

            for (int row = 0; row < width_ - 1; row++)
            {
                for (int column = 0; column < width_ - 1; column++)
                {
                    triangles_.push_back(GetVertIndex(column, row + 1, width_));
                    triangles_.push_back(GetVertIndex(column + 1, row, width_));
                    triangles_.push_back(GetVertIndex(column, row, width_));

                    triangles_.push_back(GetVertIndex(column + 1, row, width_));
                    triangles_.push_back(GetVertIndex(column, row + 1, width_));
                    triangles_.push_back(GetVertIndex(column + 1, row + 1, width_));
                }
            }
        }

        int width_;
        vector<Vector3<T>> vertices_;
        vector<int> triangles_;
        vector<Vector3<T>> normals_;
        vector<vec2<T>> uv0_;
        vector<vec2<T>> uv1_;
        vector<vec2<T>> uv2_;
        vector<vec2<T>> uv3_;
        vector<Vector3<T>> tangents_;

    private:
        static int GetVertIndex(int column, int row, int rowSize)
        {
            return column + row * rowSize;
        }

        static vector<Vector3<T>> GetVertices(int numVerts, int width, T spacing, vector<T> heights)
        {
            vector<Vector3<T>> vertices;
            vertices.reserve(numVerts);

            int rowOffset = 0;
            for (int row = 0; row < width; row++)
            {
                for (int column = 0; column < width; column++)
                {
                    Vector3 vert = Vector3{column * spacing, row * spacing, heights[column + rowOffset]};
                    vertices.push_back(vert);
                }
                rowOffset += width;
            }

            return vertices;
        }
    };

}

#endif
