#ifndef __OPENGL_EXPERIMENTS_MESH_H__
#define __OPENGL_EXPERIMENTS_MESH_H__

#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
#include <Vect3.h>



/**
 * Mesh class
 */
class Mesh
{
public:
    Mesh(const Vect3f&                 origin,
         const std::vector<Vect3f>&    vertex_list,
         const std::vector<Vect3f>&    vertex_color,
         const std::vector<Triangle>&  triangle_list):
         origin_{origin},
         vertices_{vertex_list},
         colors_{vertex_color},
         triangles_{triangle_list}
    {
    }

    const Vect3f& GetOrigin() const
    {
        return origin_;
    }

    const std::vector<Vect3f>& GetVertices() const
    {
        return vertices_;
    }

    const std::vector<Vect3f>& GetColors() const
    {
        return colors_;
    }

    const std::vector<Triangle>& GetTriangles() const
    {
        return triangles_;
    }


private:
    Vect3f                 origin_;
    std::vector<Vect3f>    vertices_;
    std::vector<Vect3f>    colors_;
    std::vector<Triangle>  triangles_;
};

#endif
