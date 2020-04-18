#ifndef __OPENGL_EXPERIMENT_WORLD_H__
#define __OPENGL_EXPERIMENT_WORLD_H__

#include <vector>
#include <memory>

#include <Mesh.h>

class World
{
public:
    static World* GetWorld()
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

    void Print() const 
    {
        std::cout << "Printing world data :" << std::endl;
        std::cout << "Vertices :";
        for(size_t i=0; i < all_vertices_.size(); ++i)
            std::cout << all_vertices_[i].xyzrgb[0] << " "
                      << all_vertices_[i].xyzrgb[1] << " "
                      << all_vertices_[i].xyzrgb[2] << " "
                      << all_vertices_[i].xyzrgb[3] << " "
                      << all_vertices_[i].xyzrgb[4] << " "
                      << all_vertices_[i].xyzrgb[5] << std::endl;

        std::cout << "Triangles:";
        for(size_t i=0; i < all_elements_.size(); ++i)
            std::cout << all_elements_[i].indices[0] << " "
                      << all_elements_[i].indices[1] << " "
                      << all_elements_[i].indices[2] << std::endl;

    }



private:
    World() = default;

    void UpdateArrays_(Mesh* mesh)
    {
        const std::vector<VertexRecord>& new_vertices = mesh->GetVertices();
        const std::vector<Triangle>&     new_elements = mesh->GetTriangles();
        all_vertices_.insert(all_vertices_.end(), new_vertices.begin(), new_vertices.end());
        all_elements_.insert(all_elements_.end(), new_elements.begin(), new_elements.end());
    }

private:
    static std::unique_ptr<World>      the_world_;
    std::vector<std::unique_ptr<Mesh>> objects_;
    std::vector<VertexRecord>          all_vertices_;
    std::vector<Triangle>              all_elements_;
};
#endif
