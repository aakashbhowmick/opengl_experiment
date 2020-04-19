#ifndef __OPENGL_EXPERIMENT_WORLD_H__
#define __OPENGL_EXPERIMENT_WORLD_H__

#include <vector>
#include <memory>

#include <Mesh.h>

struct VertexRecord
{
    float xyz[3];
    float rgb[3];
    float norm3[3];
} __attribute__((packed));

class World
{
public:
    static World* GetPtr()
    {
        if(!the_world_)
            the_world_.reset(new World());

        return the_world_.get();
    }

    void AddObject(Mesh* mesh)
    {
        objects_.emplace_back(mesh);
        UpdateArrays_(mesh);
    }

    const float* GetVertexArrayPtr() const
    {
        if(all_vertices_.empty())
            return nullptr;
        else
            return reinterpret_cast<const float*>(&all_vertices_[0]);
    }

    const unsigned int* GetElementArrayPtr() const
    {
        if(all_elements_.empty())
            return nullptr;
        else
            return reinterpret_cast<const unsigned int*>(&all_elements_[0]);
    }

    size_t GetVertexArraySizeBytes() const
    {
        return all_vertices_.size() * sizeof(VertexRecord);
    }

    size_t GetElementArraySizeBytes() const
    {
        return all_elements_.size() * sizeof(Triangle);
    }

    size_t VertexCount() const
    {
        return all_vertices_.size();
    }

    size_t ElementCount() const
    {
        return all_elements_.size();
    }

    void Print() const 
    {
        std::cout << "Printing world data :" << std::endl;
        std::cout << "Vertices :";
        for(size_t i=0; i < all_vertices_.size(); ++i)
        {
            std::cout << "{" << all_vertices_[i].xyz[0]   << " " << all_vertices_[i].xyz[1]   << " " << all_vertices_[i].xyz[2]   << "} | ";
            std::cout << "{" << all_vertices_[i].rgb[0]   << " " << all_vertices_[i].rgb[1]   << " " << all_vertices_[i].rgb[2]   << "} | ";
            std::cout << "{" << all_vertices_[i].norm3[0] << " " << all_vertices_[i].norm3[1] << " " << all_vertices_[i].norm3[2] << "}" << std::endl;
        }

        std::cout << "Triangles:";
        for(size_t i=0; i < all_elements_.size(); ++i)
            std::cout << all_elements_[i][0] << " "
                      << all_elements_[i][1] << " "
                      << all_elements_[i][2] << std::endl;
    }



private:
    World() = default;

    void UpdateArrays_(Mesh* mesh)
    {
        const std::vector<Vect3f>&   verts = mesh->GetVertices();
        const std::vector<Vect3f>&   colors= mesh->GetColors();
        const std::vector<Triangle>& trias = mesh->GetTriangles();

        // Compute vertex normals
        std::vector<Vect3f> normals(verts.size());
        for(size_t i=0; i < trias.size(); ++i)
        {
            Vect3f normal = (verts[trias[i][2]] - verts[trias[i][1]]) * (verts[trias[i][1]] - verts[trias[i][0]]).normalize();
            for(size_t j=0; j < 3; ++j)
                normals[ trias[i][j] ] += normal;
        }
        for(size_t i=0; i < normals.size(); ++i)
            normals[i].normalize();

        // Update vertices
        const size_t N = all_vertices_.size();
        all_vertices_.resize(all_vertices_.size() + verts.size());
        for(size_t i=0; i < verts.size(); ++i)
        {
            all_vertices_[N+i].xyz[0]   = verts[i][0];   all_vertices_[N+i].xyz[1]   = verts[i][1];   all_vertices_[N+i].xyz[2]   = verts[i][2]; 
            all_vertices_[N+i].rgb[0]   = colors[i][0];  all_vertices_[N+i].rgb[1]   = colors[i][1];  all_vertices_[N+i].rgb[2]   = colors[i][2]; 
            all_vertices_[N+i].norm3[0] = normals[i][0]; all_vertices_[N+i].norm3[1] = normals[i][1]; all_vertices_[N+i].norm3[2] = normals[i][2]; 
        }

        // Update triangles
        const size_t M = all_elements_.size();
        all_elements_.resize(all_elements_.size() + trias.size());
        for(size_t i=0; i < trias.size(); ++i)
            all_elements_[M+i] = trias[i] + Triangle(N); // Offset all vertices by N
    }

private:
    static std::unique_ptr<World>      the_world_;
    std::vector<std::unique_ptr<Mesh>> objects_;
    std::vector<VertexRecord>          all_vertices_;
    std::vector<Triangle>              all_elements_;
};
#endif
