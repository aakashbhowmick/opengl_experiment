#ifndef __OPENGL_EXPERIMENT_CAMERA_H__
#define __OPENGL_EXPERIMENT_CAMERA_H__

#include <iostream>

#include <Vect3.h>
#include <glm/glm.hpp>

class Camera
{
public:

    Camera():
        pos_{0.0, 0.0, 0.0},
        z_{0.0, 0.0, 1.0},
        y_{0.0, 1.0, 0.0}
    {
        UpdateViewMatrix_();
    }

    Camera(
    const Vect3f& position,
    const Vect3f& view_direction,
    const Vect3f& up_direction):
        pos_{position},
        z_{view_direction * -1.0f},
        y_{up_direction}
    {
        z_.normalize();
        y_.normalize();
        UpdateViewMatrix_();
    }

    Vect3f GetPosition() const
    {
        return pos_;
    }

    Vect3f GetViewingDirection() const
    {
        // Viewing direction (from camera to object) is opposite to
        // camera z-direction
        return z_ * -1.0f;
    }

    Vect3f GetUpDirection() const
    {
        return y_;
    }

    const glm::mat4& GetViewMatrix() const
    {
        return view_mat_;
    }

    void Translate(Vect3f trans_vector)
    {
        pos_ += trans_vector;
        UpdateViewMatrix_();
    }

private:

    void UpdateViewMatrix_()
    {
        Vect3f x  = (y_.cross(z_)).normalize();
        view_mat_ = glm::mat4(
                        x[0] , y_[0], z_[0], pos_[0],
                        x[1] , y_[1], z_[1], pos_[1],
                        x[2] , y_[2], z_[2], pos_[2],
                        0.0f , 0.0f , 0.0f , 1.0f   );

        PrintViewMatrix_();
    }

    void PrintViewMatrix_() const
    {
        std::cout << "View matrix : " << std::endl;
        std::cout << view_mat_[0][0] << "," << view_mat_[0][1] << "," << view_mat_[0][2] << "," << view_mat_[0][3] << std::endl;
        std::cout << view_mat_[1][0] << "," << view_mat_[1][1] << "," << view_mat_[1][2] << "," << view_mat_[1][3] << std::endl;
        std::cout << view_mat_[2][0] << "," << view_mat_[2][1] << "," << view_mat_[2][2] << "," << view_mat_[2][3] << std::endl;
        std::cout << view_mat_[3][0] << "," << view_mat_[3][1] << "," << view_mat_[3][2] << "," << view_mat_[3][3] << std::endl;
    }


private:
    Vect3f pos_;
    Vect3f y_;
    Vect3f z_;
    glm::mat4 view_mat_;
};

#endif
