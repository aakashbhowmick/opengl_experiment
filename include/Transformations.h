#ifndef __OPENGL_EXPERIMENTS_TRANSFORMATIONS__
#define __OPENGL_EXPERIMENTS_TRANSFORMATIONS__

#include <cmath>
#include <glm/glm.hpp>

/* In this file, we hand construct the transformation matrices.
 * Since the aim of this project is to learn the fundamentals of
 * 3D graphics, I am creating these matrices by scratch.
 */


class Transformations
{
public:

    static glm::mat4 perspective_projection(
                    double fov_degrees,      // field of view in degrees
                    double ar,               // aspect ratio (width/height) of frustum
                    double d_near,
                    double d_far)
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
        

    };
}


#endif
