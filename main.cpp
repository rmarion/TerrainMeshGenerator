#include <iostream>
#include <vector>
#include "TerrainMesh/terrain-mesh.h"

using std::vector;
using terrain_mesh_generator::terrain_mesh::TerrainMesh;

int main(void)
{
    int width = 10;
    vector<float> heights(width * width);
    for (int height = 0; height < heights.size(); height++)
    {
        heights[height] = (float)height;
    }

    TerrainMesh foo(heights, 100.0);

    std::cout << "Vertices: " << std::endl;
    for (auto &v : foo.vertices_)
    {
        std::cout << "(" << v.x << ", " << v.y << ", " << v.z << "), ";
    }

    std::cout << std::endl
              << std::endl
              << "Normals: "
              << std::endl;
    for (auto &n : foo.normals_)
    {
        std::cout << "(" << n.x << ", " << n.y << ", " << n.z << "), ";
    }

    std::cout << std::endl
              << std::endl
              << "Triangles: "
              << std::endl;
    for (auto &i : foo.triangles_)
    {
        std::cout << i << ", ";
    }

    std::cout << std::endl
              << std::endl
              << "UV0: "
              << std::endl;
    for (auto &u : foo.uv0_)
    {
        std::cout << "(" << u.x << ", " << u.y << "), ";
    }

    std::cout << std::endl;
}