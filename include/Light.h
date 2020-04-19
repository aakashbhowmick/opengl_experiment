#ifndef __OPENGL_EXPERIMENT_LIGHT_H__
#define __OPENGL_EXPERIMENT_LIGHT_H__

#include <glm/glm.hpp>

class Light
{
public:

    Light(
    const glm::vec3& position,
    const glm::vec3& color):
        color_{color},
        position_{position}
    {
    }
    


private:
    glm::vec3 color_;
    glm::vec3 position_;

};

#endif
