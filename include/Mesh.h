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
    Mesh()
    {
    }

    void Load()
    {
        vertices_.resize(4);
        vertices_[0]  =  { 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f };
        vertices_[1]  =  { 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f };
        vertices_[2]  =  {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f };
        vertices_[3]  =  {-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f };

        triangles_.resize(2);
        triangles_[0] = { 0, 1, 3 };
        triangles_[1] = { 1, 2, 3 };
    }
    

    const float* GetVertexPtr() const
    {
        return reinterpret_cast<const float*>(&vertices_[0]);
    }

    size_t GetVertexSizeBytes() const
    {
        return vertices_.size() * sizeof(VertexRecord);
    }

    
    const unsigned int* GetTriaPtr() const
    {
        return reinterpret_cast<const unsigned int*>(&triangles_[0]);
    }

    size_t GetTriaSizeBytes() const
    {
        return triangles_.size() * sizeof(Triangle);
    }


    void Print() const 
    {
        std::cout << "Printing mesh data :" << std::endl;

        for(size_t i=0; i < vertices_.size(); ++i)
            std::cout << vertices_[i].xyzrgb[0] << " "
                      << vertices_[i].xyzrgb[1] << " "
                      << vertices_[i].xyzrgb[2] << " "
                      << vertices_[i].xyzrgb[3] << " "
                      << vertices_[i].xyzrgb[4] << " "
                      << vertices_[i].xyzrgb[5] << std::endl;

        for(size_t i=0; i < triangles_.size(); ++i)
            std::cout << triangles_[i].indices[0] << " "
                      << triangles_[i].indices[1] << " "
                      << triangles_[i].indices[2] << std::endl;

    }


private:
    std::vector<VertexRecord>    vertices_;
    std::vector<Triangle> triangles_;
};

#endif