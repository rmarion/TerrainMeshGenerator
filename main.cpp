#include <iostream>
#include <vector>
#include "terrain-mesh.h"

using std::vector;
using terrain_mesh_generator::TerrainMesh;

int main(void)
{
    int width = 10;
    vector<float> heights(width * width, 0);

    TerrainMesh<float> foo(heights, 1.0);
    std::cout << "Vertices: ";
    for (auto &v : foo.vertices_)
    {
        std::cout << "(" << v.x << ", " << v.y << ", " << v.z << "), ";
    }

    std::cout << std::endl
              << "Triangles: ";
    for (auto &i : foo.triangles_)
    {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
}