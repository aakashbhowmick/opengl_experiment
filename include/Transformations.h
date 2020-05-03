#ifndef __OPENGL_EXPERIMENTS_TRANSFORMATIONS__
#define __OPENGL_EXPERIMENTS_TRANSFORMATIONS__

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/* In this file, we hand construct the transformation matrices.
 * Since the aim of this project is to learn the fundamentals of
 * 3D graphics, I am creating these matrices by scratch.
 */


class Transformations
{
public:

    static glm::mat4 PerspectiveProjection(
                      float fov_degrees,      // field of view in degrees
                      float ar,               // aspect ratio (width/height) of frustum
                      float d_near,
                      float d_far)
    {

        /**
         *                                |
         *                               *|
         *                           *    |
         *                       *        |
         *      y+       |   *            |
         *      ^        |                | 
         *      |    *   |                |
         *      o-->z-   |                |
         *           *   |                |
         *               |                |
         *               |   *            |
         *              near     *        |
         *                           *    |
         *                               *|  
         *                                |
         *                               far
         *
         *
         *                      y+
         *                      ^
         *                      |
         *          +-----------|------------+
         *          |           |            |
         *          |           |            |
         *   height |           +--------------> x+
         *          |                        |
         *          |                        |
         *          +------------------------+
         *                  width
         *
         *
         */                            
        
        // TODO: Implement on your own
        return glm::perspective(glm::radians(fov_degrees), ar, d_near, d_far);


    };

    static glm::mat4 OrthographicProjection(
                      float left,
                      float right,
                      float top,
                      float bottom,
                      float near,
                      float far)
    {
        const float& x_min = left;
        const float& x_max = right;
        const float& y_min = bottom;
        const float& y_max = top;
        const float& z_min = far;
        const float& z_max = near;

        glm::mat4 ortho;

        ortho[0][0] = 2.0f/(x_max-x_min);
        ortho[1][0] = 0.0f;
        ortho[2][0] = 0.0f;
        ortho[3][0] = (-2.0f*x_min) / (x_max - x_min) - 1.0f;

        ortho[0][1] = 0.0f;
        ortho[1][1] = 2.0f/(y_max-y_min);
        ortho[2][1] = 0.0f;
        ortho[3][1] = (-2.0f*y_min) / (y_max - y_min) - 1.0f;

        ortho[0][2] = 0.0f;
        ortho[1][2] = 0.0f;
        ortho[2][2] = 2.0f/(z_max-z_min);
        ortho[3][2] = (-2.0f*z_min) / (z_max - z_min) - 1.0f;

        ortho[0][3] = 0.0f;
        ortho[1][3] = 0.0f;
        ortho[2][3] = 0.0f;
        ortho[3][3] = 1.0f;

        return ortho;
    }

private:
    static void PrintMatrix_(const glm::mat4& mat, const std::string& msg)
    {
        std::cout << msg << std::endl;
        std::cout << mat[0][0] << "," << mat[1][0] << "," << mat[2][0] << "," << mat[3][0] << std::endl;
        std::cout << mat[0][1] << "," << mat[1][1] << "," << mat[2][1] << "," << mat[3][1] << std::endl;
        std::cout << mat[0][2] << "," << mat[1][2] << "," << mat[2][2] << "," << mat[3][2] << std::endl;
        std::cout << mat[0][3] << "," << mat[1][3] << "," << mat[2][3] << "," << mat[3][3] << std::endl;
    }

};


#endif
