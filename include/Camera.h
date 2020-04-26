#ifndef __OPENGL_EXPERIMENT_CAMERA_H__
#define __OPENGL_EXPERIMENT_CAMERA_H__

#include <Vect3.h>

class Camera
{
public:
    Camera(const Vect3f& position):
    position_{position}
    {
    }

    const Vect3f& GetPosition() const
    {
        return position_;
    }

private:
    Vect3f position_;
};

#endif
