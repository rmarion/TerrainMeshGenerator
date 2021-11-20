#include <iostream>
#include <vector>
#include "terrain-mesh.h"

using std::vector;
using terrain_mesh_generator::TerrainMesh;

int main(void)
{
    int width = 10;
    vector<float> heights(width * width);
    for (int height = 0; height < heights.size(); height++)
    {
        heights[height] = (float)height;
    }

    TerrainMesh<float> foo(heights, 1.0);

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
    std::cout << std::endl;
}