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
    static Mesh* CreateCube(float size)
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
        std::vector<VertexRecord> vertices;
        std::vector<Triangle>     triangles;
        vertices.resize(8);
        float l = size/2.0f;

        vertices[0]  =  { -l,  -l,  l, 1.0f, 0.0f, 0.0f };
        vertices[1]  =  {  l,  -l,  l, 0.0f, 1.0f, 0.0f };
        vertices[2]  =  {  l,   l,  l, 0.0f, 0.0f, 1.0f };
        vertices[3]  =  { -l,   l,  l, 1.0f, 1.0f, 1.0f };

        vertices[4]  =  { -l,  -l,  -l, 0.5f, 0.3f, 0.1f };
        vertices[5]  =  {  l,  -l,  -l, 0.3f, 2.0f, 0.8f };
        vertices[6]  =  {  l,   l,  -l, 0.0f, 0.4f, 1.0f };
        vertices[7]  =  { -l,   l,  -l, 0.5f, 0.3f, 0.8f };


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

        return new Mesh(vertices, triangles);
    }
};

#endif
