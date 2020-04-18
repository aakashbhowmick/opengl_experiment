#ifndef __OPEN_GL_EXPERIMENTS_BASIC_SHAPES__
#define __OPEN_GL_EXPERIMENTS_BASIC_SHAPES__

#include <Mesh.h>
#include <vector>

/* Class for generating basic primitive shapes.
 */
class BasicShapes 
{
public:

    /* Triangle */
    static Mesh* CreateTriangle()
    {
        std::vector<VertexRecord> vertices;
        std::vector<Triangle>     triangles;
        vertices.resize(3);
        vertices[0]  =  { 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f };
        vertices[1]  =  { 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f };
        vertices[2]  =  {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f };

        triangles.resize(1);
        triangles[0] = { 0, 1, 2 };

        return new Mesh(vertices, triangles);
    }

    /* Square */
    static Mesh* CreateSquare()
    {
        std::vector<VertexRecord> vertices;
        std::vector<Triangle>     triangles;
        vertices.resize(4);
        vertices[0]  =  { 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f };
        vertices[1]  =  { 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f };
        vertices[2]  =  {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f };
        vertices[3]  =  {-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f };

        triangles.resize(2);
        triangles[0] = { 0, 1, 3 };
        triangles[1] = { 1, 2, 3 };

        return new Mesh(vertices, triangles);
    }

    /* Cube */
    static Mesh* CreateCube()
    {
        std::vector<VertexRecord> vertices;
        std::vector<Triangle>     triangles;
        vertices.resize(6);
        vertices[0]  =  { 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f };
        vertices[1]  =  { 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f };
        vertices[2]  =  {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f };
        vertices[3]  =  {-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f };
        vertices[4]  =  {-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f };
        vertices[5]  =  {-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f };

        triangles.resize(12);
        triangles[0] = { 0, 1, 3 };
        triangles[1] = { 1, 2, 3 };
        triangles[2] = { 1, 2, 3 };
        triangles[3] = { 1, 2, 3 };
        triangles[4] = { 1, 2, 3 };
        triangles[5] = { 1, 2, 3 };
        triangles[6] = { 1, 2, 3 };
        triangles[7] = { 1, 2, 3 };
        triangles[8] = { 1, 2, 3 };
        triangles[9] = { 1, 2, 3 };
        triangles[10] = { 1, 2, 3 };
        triangles[11] = { 1, 2, 3 };

        return new Mesh(vertices, triangles);
    }
};

#endif
