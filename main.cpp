#include <vector>
#include "terrain-mesh.h"

using std::vector;
using terrain_mesh_generator::TerrainMesh;

int main(void)
{
    TerrainMesh<float> foo(vector<float>{1, 2, 3, 4, 5}, 1.0);
}