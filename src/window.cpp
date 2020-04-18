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

float rot_degrees = 0.0f;



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

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection;
    model = glm::rotate(model, glm::radians(rot_degrees), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    float fov_degree = 45.0f;
    projection = glm::perspective(glm::radians(fov_degree), 800.0f/600.0f, 0.1f, 100.0f);

    // Load, compile and link shaders
    const char* vshader_path = "/home/aakash/Code/opengl_experiment/shaders/vertex_shader1.vs";
    const char* fshader_path = "/home/aakash/Code/opengl_experiment/shaders/fragment_shader1.fs";
    Shader shader(vshader_path, fshader_path);
    shader.use();
    shader.setMat4f("model", model);
    shader.setMat4f("view", view);
    shader.setMat4f("projection", projection);

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

    /* Enable depth testing.This allows objects behind other objects 
     * to get hidden.
     */
     glEnable(GL_DEPTH_TEST);


    // render loop
    while(!glfwWindowShouldClose(window))
    {
        // Check if any input was received from the user
        processInput(window);

        // Set background color.
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Clear buffers from last render iteration, otherwise
        // it will be re-used.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update transformation matrix in shader
    model = glm::rotate(glm::mat4(1.0f), glm::radians(rot_degrees), glm::vec3(1.0f, 0.0f, 0.0f));
        shader.setMat4f("model", model);

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
    {
        glfwSetWindowShouldClose(window, true);
    }
    else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        rot_degrees += 0.5f;
        std::cout << "rot_degrees : " <<  rot_degrees << std::endl;
    }
    else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        rot_degrees -= 0.5f;
        std::cout << "rot_degrees : " <<  rot_degrees << std::endl;
    }
}

// Callback : When window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Resize OpenGL viewport to match window size
    glViewport(0, 0, width, height);
}

