#ifndef __OPEN_GL_EXPERIMENTS_BASIC_SHAPES__
#define __OPEN_GL_EXPERIMENTS_BASIC_SHAPES__

#include <Mesh.h>
#include <vector>

#include <glm/glm.hpp>

/* Class for generating basic primitive shapes.
 */
class BasicShapes 
{
public:

    /* Triangle */
    static Mesh* CreateTriangle()
    {
        std::vector<Vertex>    vertices;
        std::vector<Color>     vertex_color;
        std::vector<Triangle>  triangles;

        vertices.resize(3);
        vertices[0]  =  { 0.5f,  0.5f, 0.0f };
        vertices[1]  =  { 0.5f, -0.5f, 0.0f };
        vertices[2]  =  {-0.5f, -0.5f, 0.0f };

        vertex_color.resize(3);
        vertex_color[0] = {1.0f, 0.0f, 0.0f };
        vertex_color[1] = {0.0f, 1.0f, 0.0f };
        vertex_color[2] = {0.0f, 0.0f, 1.0f };

        triangles.resize(1);
        triangles[0] = { 0, 1, 2 };

        return new Mesh(vertices, vertex_color, triangles);
    }

    /* Square */
    static Mesh* CreateSquare()
    {
        std::vector<Vertex>   vertices;
        std::vector<Color>   color;
        std::vector<Triangle> triangles;

        vertices.resize(4);
        vertices[0]  =  { 0.5f,  0.5f, 0.0f };
        vertices[1]  =  { 0.5f, -0.5f, 0.0f };
        vertices[2]  =  {-0.5f, -0.5f, 0.0f };
        vertices[3]  =  {-0.5f,  0.5f, 0.0f };

        color.resize(4);
        color[0]  =  { 1.0f, 0.0f, 0.0f };
        color[1]  =  { 0.0f, 1.0f, 0.0f };
        color[2]  =  { 0.0f, 0.0f, 1.0f };
        color[3]  =  { 1.0f, 0.0f, 0.0f };

        triangles.resize(2);
        triangles[0] = { 0, 1, 3 };
        triangles[1] = { 1, 2, 3 };

        return new Mesh(vertices, color, triangles);
    }

    /* Cube */
    static Mesh* CreateCube(
        float size,
        glm::vec3 center)
    {
        //     
        //    7   +--------+ 6
        //       *        *| 
        //     *        *  |
        // 3 +---------+ 2 |
        //   |         |   |
        //   |         |   + 5
        //   |         | *
        //   +---------+ 
        // 0           1
        //     
        std::vector<Vertex>   vertices;
        std::vector<Color>    color;
        std::vector<Triangle> triangles;
        float l = size/2.0f;

        vertices.resize(8);
        vertices[0]  =  { center.x-l,  center.y-l,  center.z+l };
        vertices[1]  =  { center.x+l,  center.y-l,  center.z+l };
        vertices[2]  =  { center.x+l,  center.y+l,  center.z+l };
        vertices[3]  =  { center.x-l,  center.y+l,  center.z+l };

        vertices[4]  =  { center.x-l,  center.y-l,  center.z-l };
        vertices[5]  =  { center.x+l,  center.y-l,  center.z-l };
        vertices[6]  =  { center.x+l,  center.y+l,  center.z-l };
        vertices[7]  =  { center.x-l,  center.y+l,  center.z-l };

        color.resize(8);
        color[0]  =  { 1.0f, 0.0f, 0.0f };
        color[1]  =  { 0.0f, 1.0f, 0.0f };
        color[2]  =  { 0.0f, 0.0f, 1.0f };
        color[3]  =  { 1.0f, 1.0f, 1.0f };

        color[4]  =  { 0.5f, 0.3f, 0.1f };
        color[5]  =  { 0.3f, 2.0f, 0.8f };
        color[6]  =  { 0.0f, 0.4f, 1.0f };
        color[7]  =  { 0.5f, 0.3f, 0.8f };


        triangles.resize(12);
        triangles[0] = { 0, 1, 3 };
        triangles[1] = { 1, 2, 3 };
        triangles[2] = { 1, 5, 2 };
        triangles[3] = { 2, 5, 6 };
        triangles[4] = { 0, 3, 4 };
        triangles[5] = { 4, 3, 7 };
        triangles[6] = { 0, 4, 1 };
        triangles[7] = { 1, 4, 5 };
        triangles[8] = { 2, 6, 3 };
        triangles[9] = { 3, 6, 7 };
        triangles[10] = { 4, 6, 5 };
        triangles[11] = { 6, 4, 7 };

        return new Mesh(vertices, color, triangles);
    }
};

#endif
