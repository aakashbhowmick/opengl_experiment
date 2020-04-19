#ifndef __OPENGL_EXPERIMENT_LIGHT_H__
#define __OPENGL_EXPERIMENT_LIGHT_H__

#include <Vect3.h>

class Light
{
public:

    Light(
    const Vect3f& position,
    const Vect3f& color):
        color_{color},
        position_{position}
    {
    }

    const Vect3f& GetColor() const
    {
        return color_;
    }
    
    const Vect3f& GetPosition() const
    {
        return position_;
    }


private:
    Vect3f color_;
    Vect3f position_;

};

#endif
