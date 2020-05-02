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
};


#endif
