#include "terrain-mesh.h"

namespace terrain_mesh_generator::terrain_mesh
{
    using std::vector;
    using vector_math::Vector3;

    TerrainMesh::TerrainMesh(vector<float> heights, float spacing)
    {
        // terrain meshes will always be square
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

        uv0_ = GetUvs(width_);
        uv1_ = GetUvs(width_);
        uv2_ = GetUvs(width_);
        uv3_ = GetUvs(width_);
    }

    int width_;
    vector<Vector3> vertices_;
    vector<int> triangles_;
    vector<Vector3> normals_;
    vector<vec2<float>> uv0_;
    vector<vec2<float>> uv1_;
    vector<vec2<float>> uv2_;
    vector<vec2<float>> uv3_;
    vector<Vector3> tangents_;

    int TerrainMesh::GetVertIndex(int column, int row, int rowSize)
    {
        return column + row * rowSize;
    }

    vector<Vector3> TerrainMesh::GetVertices(int numVerts, int width, float spacing, vector<float> heights)
    {
        vector<Vector3> vertices;
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

    vector<Vector3> TerrainMesh::GetNormals(vector<Vector3> vertices, int width)
    {
        vector<Vector3> normals;
        normals.reserve(vertices.size());

        // In order to make these smooth, we have to make each normal the average of the
        // normals for adjacent points.
        //
        // However, if we're calculating these in a '+' pattern, then there won't be any
        // duplicates. Therefore we should calculate these per vertex as we iterate over them
        //
        // fHere could be optimization done with the vertex subtraction
        int maxWidth = width - 1;
        int currentIndex;
        Vector3 currentSum;
        for (int row = 0; row < width; row++)
        {
            for (int column = 0; column < width; column++)
            {
                currentSum = Vector3::zero();
                currentIndex = GetVertIndex(column, row, width);
                if (column > 0)
                {
                    if (row > 0)
                    {
                        // ((x, y) - (x - 1, y)) x ((x, y) - (x, y - 1))
                        auto lhs = vertices[currentIndex] - vertices[GetVertIndex(column - 1, row, width)];
                        auto rhs = vertices[currentIndex] - vertices[GetVertIndex(column, row - 1, width)];
                        auto wat = lhs * rhs;
                        currentSum += lhs * rhs;
                    }

                    if (row < maxWidth)
                    {
                        // ((x, y) - (x - 1, y)) x ((x, y) - (x, y + 1))
                        auto lhs = vertices[currentIndex] - vertices[GetVertIndex(column - 1, row, width)];
                        auto rhs = vertices[currentIndex] - vertices[GetVertIndex(column, row + 1, width)];
                        currentSum += lhs * rhs;
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
                    }

                    if (row < maxWidth)
                    {
                        // ((x, y) - (x + 1, y)) x ((x, y) - (x, y + 1))
                        auto lhs = vertices[currentIndex] - vertices[GetVertIndex(column + 1, row, width)];
                        auto rhs = vertices[currentIndex] - vertices[GetVertIndex(column, row + 1, width)];
                        currentSum += lhs * rhs;
                    }
                }
                currentSum.normalize();
                normals.push_back(currentSum); // currentCount will always be at least 1
            }
        }

        return normals;
    }

    vector<int> TerrainMesh::GetTriangles(int width)
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

    vector<vec2<float>> TerrainMesh::GetUvs(float width)
    {
        vector<vec2<float>> uvs;
        uvs.reserve(width * width);

        for (int row = 0; row < width; row++)
        {
            for (int column = 0; column < width; column++)
            {
                uvs.push_back(vec2<float>(column / width, row / width));
            }
        }

        return uvs;
    }
};