#include "Math/Vector.h"
#include <vector>
#include <map>
#include <string.h>
#include <glfw3.h>

struct packedVertex
{
    Vector3 position;
    Vector2 uvs;
    Vector3 normal;
    bool operator<(const packedVertex that)const
    {
        return memcmp((void*)this, (void*)&that, sizeof(packedVertex))>0;
    }
};

inline bool getSimilarVertexIndex
(
    packedVertex& packed,
    std::map<packedVertex, unsigned short>& vertexOutIndex,
    unsigned short& result
)
{
    std::map<packedVertex, unsigned short>::iterator it = vertexOutIndex.find(packed);
    if(it == vertexOutIndex.end())
        return false;
    else
    {
        result = it->second;
        return true;
    }
}

inline void indexVBO
(
    std::vector<Vector3>& in_vertices,
    std::vector<Vector3>& in_normals,
    std::vector<Vector2>& in_uvs,

    std::vector<unsigned short>& out_indices,
    std::vector<Vector3>& out_vertices,
    std::vector<Vector3>& out_normals,
    std::vector<Vector2>& out_uvs
)
{
    std::map<packedVertex, unsigned short>vertexOutIndex;
    for(unsigned int i = 0; i < in_vertices.size(); i++)
    {
        packedVertex packed;
        if(!in_vertices.empty() && !in_uvs.empty() && !in_normals.empty())
            packed = {in_vertices[i], in_uvs[i], in_normals[i]};
        else if(in_uvs.empty()){
            packed.position = in_vertices[i];
            packed.normal = in_normals[i];
        }

        unsigned short index;
        bool found = getSimilarVertexIndex(packed, vertexOutIndex, index);

        if(found)
            out_indices.push_back(index);
        else
        {
            if(!in_vertices.empty())
                out_vertices.push_back(in_vertices[i]);
            if(!in_normals.empty())
                out_normals. push_back(in_normals[i]);
            if(!in_uvs.empty())
                out_uvs.     push_back(in_uvs[i]);
            unsigned short newIndex = (unsigned short)out_vertices.size() - 1;
            out_indices.push_back(newIndex);
            vertexOutIndex[packed] = newIndex;
        }
    }
}


