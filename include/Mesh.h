#ifndef __OPENGL_EXPERIMENTS_MESH_H__
#define __OPENGL_EXPERIMENTS_MESH_H__

#include <vector>
#include <cstring>
#include <iostream>
#include <cassert>

// Vertex 
struct Vertex 
{
    float xyz[3];

    void operator=(const float* array3f)
    {
        xyz[0]=array3f[0]; xyz[1]=array3f[1]; xyz[2]=array3f[2];
    }

};

// Color
struct Color
{
    float rgb[3];

    void operator=(const float* array3f)
    {
        rgb[0]=array3f[0]; rgb[1]=array3f[1]; rgb[2]=array3f[2];
    }
};

// VertexRecord
struct VertexRecord
{
    float xyzrgb[6];

    VertexRecord(const Vertex& v, const Color& c)
    {
        xyzrgb[0] = v.xyz[0]; xyzrgb[1] = v.xyz[1]; xyzrgb[2] = v.xyz[2];
        xyzrgb[3] = c.rgb[0]; xyzrgb[4] = c.rgb[1]; xyzrgb[5] = c.rgb[2];
    }

} __attribute__((packed));


// Triangle 
struct Triangle
{
    unsigned int indices[3];

    void operator= (const unsigned int* index)
    {
        indices[0] = index[0]; indices[1] = index[1];  indices[2] = index[2]; 
    }
};

/**
 * Mesh class
 */
class Mesh
{
public:
    Mesh(const std::vector<Vertex>&    vertex_list,
         const std::vector<Color>&     vertex_color,
         const std::vector<Triangle>&  triangle_list):
         triangles_{triangle_list}
    {
        assert(vertex_list.size() == vertex_color.size());

        // Merge vertex and color list
        vertices_.reserve(vertex_list.size());
        for(size_t i=0; i < vertex_list.size(); ++i)
        {
            vertices_.emplace_back(vertex_list[i], vertex_color[i]);
        }
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
