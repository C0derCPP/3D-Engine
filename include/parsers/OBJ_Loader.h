#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <glfw3.h>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>

#include "Math/Vector.h"

class OBJ_Loader
{
    public:
        std::vector< float > vertices;
        bool loadOBJ
        (
            const char * path,
            std::vector < Vector3 > & out_vertices,
            std::vector < Vector2 > & out_uvs,
            std::vector < Vector3 > & out_normals,
            const int face
        );

    protected:
    private:
        std::vector< unsigned int >
        vertexIndices,
        uvIndices,
        normalIndices;

        std::vector< Vector3 > temp_vertices;
        std::vector< Vector2 > temp_uvs;
        std::vector< Vector3 > temp_normals;
};

inline bool OBJ_Loader::loadOBJ
(
    const char * path,
    std::vector < Vector3 > & out_vertices,
    std::vector < Vector2 > & out_uvs,
    std::vector < Vector3 > & out_normals,
    const int face
)
{
    FILE * file = fopen(path, "r");
    if( file == NULL ){
        std::cout << "Unable to open file /" << path << "/" << std::endl;
        return false;
    }
    else
        std::cout << "\nsuccesfully loaded /" << path << "/" << std::endl;

    while( 1 ){
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;

        if ( strcmp( lineHeader, "v" ) == 0 ){
            Vector3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        }
        else if ( strcmp( lineHeader, "vt" ) == 0 ){
            Vector2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            temp_uvs.push_back(uv);
        }

        else if ( strcmp( lineHeader, "vn" ) == 0 ){
            Vector3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }
        else if ( strcmp( lineHeader, "f" ) == 0){
            unsigned int vertexIndex [3], uvIndex [3], normalIndex [3];
            if(face == 1){
                // ( 1 )  f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
                if (fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                    &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                    &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                    &vertexIndex[2], &uvIndex[2], &normalIndex[2]) == 9)
                {
                    vertexIndices   .push_back(vertexIndex[0]);
                    vertexIndices   .push_back(vertexIndex[1]);
                    vertexIndices   .push_back(vertexIndex[2]);
                    uvIndices       .push_back    (uvIndex[0]);
                    uvIndices       .push_back    (uvIndex[1]);
                    uvIndices       .push_back    (uvIndex[2]);
                    normalIndices   .push_back(normalIndex[0]);
                    normalIndices   .push_back(normalIndex[1]);
                    normalIndices   .push_back(normalIndex[2]);
                }
            }

            else if(face == 2)
            {
                // ( 2 )  f v1//vn1 v2//vn2 v3//vn3
                if (fscanf(file, "%d//%d %d//%d %d//%d\n",
                    &vertexIndex[0], &normalIndex[0],
                    &vertexIndex[1], &normalIndex[1],
                    &vertexIndex[2], &normalIndex[2]) == 6)
                {
                    vertexIndices    .push_back(vertexIndex[0]);
                    vertexIndices    .push_back(vertexIndex[1]);
                    vertexIndices    .push_back(vertexIndex[2]);
                    normalIndices    .push_back(normalIndex[0]);
                    normalIndices    .push_back(normalIndex[1]);
                    normalIndices    .push_back(normalIndex[2]);
                }
            }
            else if(face == 3)
            {
                // ( 3 )  f v1 v2 v3
                if (fscanf(file, "%d %d %d\n",
                    &vertexIndex[0],
                    &vertexIndex[1],
                    &vertexIndex[2]) == 3)
                {
                    vertexIndices.push_back(vertexIndex[0]);
                    vertexIndices.push_back(vertexIndex[1]);
                    vertexIndices.push_back(vertexIndex[2]);
                }
            }
        }
    }

    if(face == 1 || face == 2 || face == 3)
    {
        for(unsigned int i = 0; i < vertexIndices.size(); i++)
        {
            unsigned int vertexIndex = vertexIndices[i];
            Vector3 vertex = temp_vertices[ vertexIndex-1 ];
            out_vertices.push_back(vertex);
        }
    }
    if(face == 1)
    {
        for(unsigned int i = 0; i < uvIndices.size(); i++)
        {
            unsigned int uvIndex = uvIndices[i];
            Vector2 uv = temp_uvs[ uvIndex-1 ];
            out_uvs.push_back(uv);
        }
    }
    if(face == 1 || face == 2)
    {
        for(unsigned int i = 0; i < normalIndices.size(); i++)
        {
            unsigned int normalIndex = normalIndices[i];
            Vector3 normal = temp_normals[ normalIndex-1 ];
            out_normals.push_back(normal);
        }
    }
    std::cout << path << "... done" << std::endl;
    return true;
}

#endif // OBJ_LOADER_H
