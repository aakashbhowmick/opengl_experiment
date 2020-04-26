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
        cam_z_{0.0f, 0.0f, 1.0f}
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
    }

    Vect3f GetUpDirection() const
    {
        return cam_y_;
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

    void Reset()
    {
        *this = Camera();
    }

private:

    void UpdateViewMatrix_()
    {
        Vect3f cam_x_  = (cam_y_.cross(cam_z_)).normalize();
        view_mat_[0] = glm::vec4(cam_x_.glm(), 0.0f);  // col 0
        view_mat_[1] = glm::vec4(cam_y_.glm(), 0.0f);  // col 1
        view_mat_[2] = glm::vec4(cam_z_.glm(), 0.0f);  // col 2
        view_mat_[3] = glm::vec4(pos_.glm()  , 1.0f);  // col 3

        PrintMatrix_(view_mat_, "View Matrix");
    }

    static void PrintMatrix_(const glm::mat4& mat, const std::string& msg)
    {
        std::cout << msg << std::endl;
        std::cout << mat[0][0] << "," << mat[1][0] << "," << mat[2][0] << "," << mat[3][0] << std::endl;
        std::cout << mat[0][1] << "," << mat[1][1] << "," << mat[2][1] << "," << mat[3][1] << std::endl;
        std::cout << mat[0][2] << "," << mat[1][2] << "," << mat[2][2] << "," << mat[3][2] << std::endl;
        std::cout << mat[0][3] << "," << mat[1][3] << "," << mat[2][3] << "," << mat[3][3] << std::endl;
    }


private:

    Vect3f pos_;
    Vect3f cam_y_;
    Vect3f cam_z_;

    glm::mat4 view_mat_;
};

#endif
