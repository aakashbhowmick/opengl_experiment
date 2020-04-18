#ifndef __OPENGL_EXPERIMENTS_MESH_H__
#define __OPENGL_EXPERIMENTS_MESH_H__

#include <vector>
#include <cstring>
#include <iostream>

// Point 
struct Point
{
    float xyz[3];
};

// Color
struct Color
{
    float rgb[3];
};

// Vertex
struct VertexRecord
{
    float xyzrgb[6];

    const VertexRecord& operator= (const VertexRecord& other)
    {
        CopyArray(other.xyzrgb);
        return *this;
    }

    const VertexRecord& operator= (const float* xyz_rgb)
    {
        CopyArray(xyz_rgb);
        return *this;
    }

    void CopyArray(const float* xyz_rgb)
    {
        memcpy(xyzrgb, xyz_rgb, sizeof(float)*6);
    }
};


// Triangle 
struct Triangle
{
    unsigned int indices[3];

    const Triangle& operator= (const unsigned int* index)
    {
        CopyArray(index);
        return *this;
    }

    void CopyArray(const unsigned int* index)
    {
        memcpy(indices, index, sizeof(unsigned int)*3);
    }
};

/**
 * Mesh class
 */
class Mesh
{
public:
    Mesh(const std::vector<VertexRecord>& vertex_list,
         const std::vector<Triangle>& triangle_list):
         vertices_{vertex_list},
         triangles_{triangle_list}
    {
    }

    const std::vector<VertexRecord>& GetVertices() const
    {
        return vertices_;
    }

    const std::vector<Triangle>& GetTriangles() const
    {
        return triangles_;
    }


private:
    std::vector<VertexRecord> vertices_;
    std::vector<Triangle>     triangles_;
};

#endif
