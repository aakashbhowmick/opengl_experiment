#ifndef __OPENGL_EXPERIMENT_CAMERA_H__
#define __OPENGL_EXPERIMENT_CAMERA_H__

#include <Vect3.h>

class Camera
{
public:

    Camera():
        position_{0.0, 0.0, 0.0},
        view_dir_{0.0, 0.0, -1.0},
        up_dir_{0.0, 1.0, 0.0}
    {
    }

    Camera(
    const Vect3f& position,
    const Vect3f& view_direction,
    const Vect3f& up_direction):
        position_{position},
        view_dir_{view_direction},
        up_dir_{up_direction}
    {
        view_dir_.normalize();
        up_dir_.normalize();
    }

    const Vect3f& GetPosition() const
    {
        return position_;
    }

    const Vect3f& GetViewingDirection() const
    {
        return view_dir_;
    }

    const Vect3f& GetUpDirection() const
    {
        return up_dir_;
    }

private:
    Vect3f position_;
    Vect3f view_dir_;
    Vect3f up_dir_;
};

#endif
