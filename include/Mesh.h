#ifndef __OPENGL_EXPERIMENTS_MESH_H__
#define __OPENGL_EXPERIMENTS_MESH_H__

#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

#include <Vect3.h>

// Vertex
struct Vertex
{
    Vect3f pos;
    Vect3f color;

    Vertex(const Vect3f& p, const Vect3f& c):
      pos{p}, color{c}
    {
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
    Mesh(const std::vector<Vect3f>&    vertex_list,
         const std::vector<Vect3f>&     vertex_color,
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

    const std::vector<Vertex>& GetVertices() const
    {
        return vertices_;
    }

    const std::vector<Triangle>& GetTriangles() const
    {
        return triangles_;
    }


private:
    std::vector<Vertex> vertices_;
    std::vector<Triangle>     triangles_;
};

#endif
