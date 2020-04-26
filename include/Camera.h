#ifndef __OPENGL_EXPERIMENT_CAMERA_H__
#define __OPENGL_EXPERIMENT_CAMERA_H__

#include <iostream>
#include <string>

#include <Vect3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:

    Camera():
        pos_{0.0f, 0.0f, 0.0f},
        cam_y_{0.0f, 1.0f, 0.0f},
        cam_z_{0.0f, 0.0f, 1.0f},
        ref_mat_{1.0f}
    {
        UpdateViewMatrix_();
    }

    Camera(
    const Vect3f& position,
    const Vect3f& view_direction,
    const Vect3f& up_direction):
        pos_{position},
        cam_z_{view_direction * -1.0f},
        cam_y_{up_direction}
    {
        cam_z_.normalize();
        cam_y_.normalize();
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
        return cam_z_ * -1.0f;
    }

    Vect3f GetUpDirection() const
    {
        return cam_y_;
    }

    const glm::mat4& GetViewMatrix() const
    {
        return view_mat_;
    }

    const glm::mat4& GetRefMatrix() const
    {
        return ref_mat_;
    }

    void Translate(Vect3f trans_vector)
    {
        pos_ += trans_vector;
        ref_mat_ = glm::translate(ref_mat_, glm::vec3(trans_vector[0], trans_vector[1], trans_vector[2]));
        UpdateViewMatrix_();
    }

    void Reset()
    {
        *this = Camera();
    }

private:

    void UpdateViewMatrix_()
    {
        Vect3f cam_x_  = (cam_y_.cross(cam_z_)).normalize();
        view_mat_ = glm::mat4(
                        cam_x_[0]   , cam_x_[1]  , cam_x_[2]  , 0.0f,
                        cam_y_[0]   , cam_y_[1]  , cam_y_[2]  , 0.0f,
                        cam_z_[0]   , cam_z_[1]  , cam_z_[2]  , 0.0f,
                        pos_[0]     , pos_[1]    , pos_[2]    , 1.0f );

        PrintMatrix_(view_mat_, "View Matrix");
        PrintMatrix_(ref_mat_, "Ref Matrix");
    }

    static void PrintMatrix_(const glm::mat4& mat, const std::string& msg)
    {
        std::cout << msg << std::endl;
        std::cout << mat[0][0] << "," << mat[0][1] << "," << mat[0][2] << "," << mat[0][3] << std::endl;
        std::cout << mat[1][0] << "," << mat[1][1] << "," << mat[1][2] << "," << mat[1][3] << std::endl;
        std::cout << mat[2][0] << "," << mat[2][1] << "," << mat[2][2] << "," << mat[2][3] << std::endl;
        std::cout << mat[3][0] << "," << mat[3][1] << "," << mat[3][2] << "," << mat[3][3] << std::endl;
    }


private:
    Vect3f pos_;
    Vect3f cam_y_;
    Vect3f cam_z_;
    glm::mat4 view_mat_;
    glm::mat4 ref_mat_;
};

#endif
