#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <exception>
#include <iostream>

#include <Mesh.h>
#include <Shader.h>

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;



//**** MAIN *****
int main()
{
    // glfw initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGLExperiment", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Ask GLAD to load all OpenGL function pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialized GLAD" << std::endl;
        return -1;
    }

    // Load, compile and link shaders
    const char* vshader_path = "/home/aakash/Code/opengl_experiment/shaders/vertex_shader1.vs";
    const char* fshader_path = "/home/aakash/Code/opengl_experiment/shaders/fragment_shader1.fs";
    Shader shader(vshader_path, fshader_path);
    shader.use();
    glm::mat4 transform_mat(1.0f);
    transform_mat = glm::rotate(transform_mat, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 0.1f));
    shader.setMat4f("vertex_transform", transform_mat);

    // Load mesh data
    Mesh mesh;
    mesh.Load();
    mesh.Print();
    const float* vertex_array = mesh.GetVertexPtr();
    size_t vertex_array_size = mesh.GetVertexSizeBytes();
    const unsigned int* tria_array = mesh.GetTriaPtr();
    size_t tria_array_size = mesh.GetTriaSizeBytes();

    /* Create a vertex-array object
     * A VAO stores meta-data about the VBO.
     */
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    // Make this array object the active vertex array
    glBindVertexArray(VAO);

    /* Create a buffer object.
     * A buffer object is a block of memory for storing data.
     */
    // Create a new buffer object
    GLuint VBO;
    glGenBuffers(1, &VBO);
    // Bind the buffer to the active vertex-buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    // Copy data to the buffer
    glBufferData(GL_ARRAY_BUFFER, vertex_array_size, vertex_array, GL_STATIC_DRAW);
    
    GLuint vert_attribute_coord = 0;   
    GLuint vert_attribute_color = 1;  
    GLuint coord_comp = 3;              // 3 co-ordinates per vertex
    GLuint color_comp = 3;              // 3 co-ordinates per color
    GLsizei stride = 6*sizeof(float);   // Stride size
    void* coord_offset = NULL;          // Offset from start
    void* color_offset = (void*)(3*sizeof(float));

    glVertexAttribPointer(vert_attribute_coord, coord_comp, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glVertexAttribPointer(vert_attribute_color, color_comp, GL_FLOAT, GL_FALSE, stride, (void*)(3*sizeof(float)) );
    glEnableVertexAttribArray(vert_attribute_coord);
    glEnableVertexAttribArray(vert_attribute_color);

    /* Create an element buffer object (EBO)
     */
     GLuint EBO;
     glGenBuffers(1, &EBO);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, tria_array_size, tria_array, GL_STATIC_DRAW);


    // render loop
    while(!glfwWindowShouldClose(window))
    {
        // Check if any input was received from the user
        processInput(window);

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Set shader program
        //glUseProgram(shaderProgram);
        
        // Draw elements
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        GLsizei elem_array_size = 6;
        void* offset = 0;
        glDrawElements(GL_TRIANGLES, elem_array_size, GL_UNSIGNED_INT, offset);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Deallocate resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    glfwTerminate();
    return 0;
}

// Callback : When a key is pressed
void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Callback : When window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Resize OpenGL viewport to match window size
    glViewport(0, 0, width, height);
}

