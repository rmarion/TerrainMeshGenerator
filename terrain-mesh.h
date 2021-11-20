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

            normals_ = GetNormals(vertices_, width_);

            triangles_ = GetTriangles(width_);
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

        static vector<Vector3<T>> GetNormals(vector<Vector3<T>> vertices, int width)
        {
            vector<Vector3<T>> normals;
            normals.reserve(vertices.size());

            // In order to make these smooth, we have to make each normal the average of the
            // normals for adjacent points.
            //
            // However, if we're calculating these in a '+' pattern, then there won't be any
            // duplicates. Therefore we should calculate these per vertex as we iterate over them
            //
            // There could be optimization done with the vertex subtraction
            int maxWidth = width - 1;
            int currentCount;
            int currentIndex;
            Vector3<T> currentSum;
            for (int row = 0; row < width; row++)
            {
                for (int column = 0; column < width; column++)
                {
                    currentCount = 0;
                    currentSum = Vector3<T>(0.1, 0.1, 0.1);
                    currentIndex = GetVertIndex(column, row, width);
                    if (column > 0)
                    {
                        if (row > 0)
                        {
                            // ((x, y) - (x - 1, y)) x ((x, y) - (x, y - 1))
                            auto lhs = vertices[currentIndex] - vertices[GetVertIndex(column - 1, row, width)];
                            auto rhs = vertices[currentIndex] - vertices[GetVertIndex(column, row - 1, width)];
                            currentSum += lhs * rhs;
                            currentCount++;
                        }

                        if (row < maxWidth)
                        {
                            // ((x, y) - (x - 1, y)) x ((x, y) - (x, y + 1))
                            auto lhs = vertices[currentIndex] - vertices[GetVertIndex(column - 1, row, width)];
                            auto rhs = vertices[currentIndex] - vertices[GetVertIndex(column, row + 1, width)];
                            currentSum += lhs * rhs;
                            currentCount++;
                        }
                    }

                    if (column < maxWidth)
                    {
                        if (row > 0)
                        {
                            // ((x, y) - (x + 1, y)) x ((x, y) - (x, y - 1))
                            auto lhs = vertices[currentIndex] - vertices[GetVertIndex(column + 1, row, width)];
                            auto rhs = vertices[currentIndex] - vertices[GetVertIndex(column, row - 1, width)];
                            currentSum += lhs * rhs;
                            currentCount++;
                        }

                        if (row < maxWidth)
                        {
                            // ((x, y) - (x + 1, y)) x ((x, y) - (x, y + 1))
                            auto lhs = vertices[currentIndex] - vertices[GetVertIndex(column + 1, row, width)];
                            auto rhs = vertices[currentIndex] - vertices[GetVertIndex(column, row + 1, width)];
                            currentSum += lhs * rhs;
                            currentCount++;
                        }
                    }
                    normals.push_back(currentSum / currentCount); // currentCount will always be at least 1
                }
            }

            return normals;
        }

        static vector<int> GetTriangles(int width)
        {
            vector<int> triangles;
            triangles.reserve((width - 1) * (width - 1));

            for (int row = 0; row < width - 1; row++)
            {
                for (int column = 0; column < width - 1; column++)
                {
                    triangles.push_back(GetVertIndex(column, row + 1, width));
                    triangles.push_back(GetVertIndex(column + 1, row, width));
                    triangles.push_back(GetVertIndex(column, row, width));

                    triangles.push_back(GetVertIndex(column + 1, row, width));
                    triangles.push_back(GetVertIndex(column, row + 1, width));
                    triangles.push_back(GetVertIndex(column + 1, row + 1, width));
                }
            }

            return triangles;
        }
    };

}

#endif
