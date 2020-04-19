#ifndef __OPEN_GL_EXPERIMENTS_BASIC_SHAPES__
#define __OPEN_GL_EXPERIMENTS_BASIC_SHAPES__

#include <Mesh.h>
#include <vector>

#include <glm/glm.hpp>
#include <Vect3.h>

/* Class for generating basic primitive shapes.
 */
class BasicShapes 
{
public:

    /* Triangle */
    static Mesh* CreateTriangle()
    {
        std::vector<Vect3f>    vertices;
        std::vector<Vect3f>     vertex_color;
        std::vector<Triangle>  triangles;

        vertices.resize(3);
        vertices[0].Set( 0.5f,  0.5f, 0.0f );
        vertices[1].Set( 0.5f, -0.5f, 0.0f );
        vertices[2].Set(-0.5f, -0.5f, 0.0f );

        vertex_color.resize(3);
        vertex_color[0].Set(1.0f, 0.0f, 0.0f );
        vertex_color[1].Set(0.0f, 1.0f, 0.0f );
        vertex_color[2].Set(0.0f, 0.0f, 1.0f );

        triangles.resize(1);
        triangles[0].Set( 0, 1, 2 );

        return new Mesh(Vect3f(0.0f), vertices, vertex_color, triangles);
    }

    /* Square */
    static Mesh* CreateSquare()
    {
        std::vector<Vect3f>   vertices;
        std::vector<Vect3f>   color;
        std::vector<Triangle> triangles;

        vertices.resize(4);
        vertices[0].Set( 0.5f,  0.5f, 0.0f );
        vertices[1].Set( 0.5f, -0.5f, 0.0f );
        vertices[2].Set(-0.5f, -0.5f, 0.0f );
        vertices[3].Set(-0.5f,  0.5f, 0.0f );

        color.resize(4);
        color[0].Set( 1.0f, 0.0f, 0.0f );
        color[1].Set( 0.0f, 1.0f, 0.0f );
        color[2].Set( 0.0f, 0.0f, 1.0f );
        color[3].Set( 1.0f, 0.0f, 0.0f );

        triangles.resize(2);
        triangles[0].Set( 0, 1, 3 );
        triangles[1].Set( 1, 2, 3 );

        return new Mesh(Vect3f(0.0f), vertices, color, triangles);
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
        std::vector<Vect3f>    vertices;
        std::vector<Vect3f>    color;
        std::vector<Triangle> triangles;
        float l = size/2.0f;

        vertices.resize(8);
        vertices[0].Set( center.x-l,  center.y-l,  center.z+l );
        vertices[1].Set( center.x+l,  center.y-l,  center.z+l );
        vertices[2].Set( center.x+l,  center.y+l,  center.z+l );
        vertices[3].Set( center.x-l,  center.y+l,  center.z+l );

        vertices[4].Set( center.x-l,  center.y-l,  center.z-l );
        vertices[5].Set( center.x+l,  center.y-l,  center.z-l );
        vertices[6].Set( center.x+l,  center.y+l,  center.z-l );
        vertices[7].Set( center.x-l,  center.y+l,  center.z-l );

        color.resize(8);
        color[0].Set( 1.0f, 0.0f, 0.0f );
        color[1].Set( 0.0f, 1.0f, 0.0f );
        color[2].Set( 0.0f, 0.0f, 1.0f );
        color[3].Set( 1.0f, 1.0f, 1.0f );

        color[4].Set( 0.5f, 0.3f, 0.1f );
        color[5].Set( 0.3f, 2.0f, 0.8f );
        color[6].Set( 0.0f, 0.4f, 1.0f );
        color[7].Set( 0.5f, 0.3f, 0.8f );


        triangles.resize(12);
        triangles[0].Set( 0, 1, 3 );
        triangles[1].Set( 1, 2, 3 );
        triangles[2].Set( 1, 5, 2 );
        triangles[3].Set( 2, 5, 6 );
        triangles[4].Set( 0, 3, 4 );
        triangles[5].Set( 4, 3, 7 );
        triangles[6].Set( 0, 4, 1 );
        triangles[7].Set( 1, 4, 5 );
        triangles[8].Set( 2, 6, 3 );
        triangles[9].Set( 3, 6, 7 );
        triangles[10].Set( 4, 6, 5 );
        triangles[11].Set( 6, 4, 7 );

        return new Mesh(Vect3f(0.0f), vertices, color, triangles);
    }
};

#endif
