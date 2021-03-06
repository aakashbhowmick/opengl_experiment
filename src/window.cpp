#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <exception>
#include <iostream>
#include <memory>
#include <string>

#include <World.h>
#include <Mesh.h>
#include <Shader.h>
#include <BasicShapes.h>
#include <Transformations.h>

typedef void (*WindowResizeCallback)(GLFWwindow* , int , int );

// Function forward declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLFWwindow* initializeGLFW( unsigned int window_width, unsigned int window_height, const std::string& window_title, WindowResizeCallback callback);
void RenderLoop( GLFWwindow* window, GLuint VAO, GLuint EBO, Shader& shader);
void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;
float light_radius = 10.0;
float light_angle  = 0.0;

struct CommandLineOptions
{
    bool wireframeMode = false;
};

CommandLineOptions ProcessCommandLineOptions(int argc, char** argv);

//**** MAIN *****
int main(int argc, char**argv)
{

    CommandLineOptions options = ProcessCommandLineOptions(argc, argv);

    // Initialize GLFW window
    GLFWwindow* window = initializeGLFW(SCR_WIDTH, SCR_HEIGHT, "OpenGLExperiment", &(framebuffer_size_callback));

    // Ask GLAD to load all OpenGL function pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialized GLAD" << std::endl;
        return -1;
    }

    if(options.wireframeMode)
    {
        std::cout << "Turning on wireframe mode" << std::endl;
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        std::cout << "Turning on fill mode" << std::endl;
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    glEnable(GL_DEPTH_TEST);  // Enable depth testing

    World* the_world = World::GetPtr();
    Camera& the_camera = the_world->GetCamera();
    the_camera.Translate(Vect3f(0.0f, 0.0f, -3.0f));


    // Load, compile and link shaders
    const char* vshader_path = "/home/aakash/Code/opengl_experiment/shaders/with_light.vert";
    const char* fshader_path = "/home/aakash/Code/opengl_experiment/shaders/with_light.frag";
    Shader shader(vshader_path, fshader_path);
    shader.use();

    float fov_degree = 45.0f;
    //glm::mat4 projection = Transformations::PerspectiveProjection(fov_degree, 800.0f/600.0f, 0.1f, 100.0f);
    glm::mat4 projection = Transformations::OrthographicProjection(-1.0f, 1.0f, -1.0f, 1.0f, -5.0f, 5.0f);
    glm::mat4 proj_inv   = glm::inverse(projection);
    shader.setMat4f("model", glm::mat4(1.0f));
    shader.setMat4f("view", glm::mat4(1.0f));
    shader.setMat4f("projection", projection);
    shader.setVec3("viewing_pos", the_camera.GetPosition().glm());

    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    shader.setVec3("lightColor", lightColor);

    // Load mesh data
    the_world->AddObject(BasicShapes::CreateCube2(0.5, glm::vec3(0.0f)));
    the_world->Print();
    const float* vertex_array      = the_world->GetVertexArrayPtr();
    size_t vertex_array_size       = the_world->GetVertexArraySizeBytes();
    const unsigned int* tria_array = the_world->GetElementArrayPtr();
    size_t tria_array_size         = the_world->GetElementArraySizeBytes();

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
    // Bind the buffer to the active vertex array object
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    // Copy data to the buffer
    glBufferData(GL_ARRAY_BUFFER, vertex_array_size, vertex_array, GL_STATIC_DRAW);

    GLuint vert_attribute_coord = 0;   
    GLuint vert_attribute_color = 1;  
    GLuint vert_attribute_norm  = 2;  
    GLuint coord_comp = 3;                   // 3 co-ordinates per vertex
    GLuint color_comp = 3;                   // 3 co-ordinates per color
    GLuint norm_comp  = 3;                   // 3 co-ordinates per normal
    GLsizei stride = sizeof(VertexRecord);   // Stride size

    glVertexAttribPointer(vert_attribute_coord, coord_comp, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glVertexAttribPointer(vert_attribute_color, color_comp, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(VertexRecord::xyz)) );
    glVertexAttribPointer(vert_attribute_norm , norm_comp,  GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(VertexRecord::xyz) + sizeof(VertexRecord::rgb)) );
    glEnableVertexAttribArray(vert_attribute_coord);
    glEnableVertexAttribArray(vert_attribute_color);
    glEnableVertexAttribArray(vert_attribute_norm);

    /* Create an element buffer object (EBO)
     */
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tria_array_size, tria_array, GL_STATIC_DRAW);


    // Rendering loop
    RenderLoop( window, VAO, EBO, shader);

    // Deallocate resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

// Initializes a GLFW window.
// Returns NULL on failure.
GLFWwindow* initializeGLFW(
                unsigned int window_width,
                unsigned int window_height,
                const std::string& window_title,
                WindowResizeCallback callback)
                
{
    // glfw initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, window_title.c_str(), NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, callback);
    glfwSetKeyCallback(window, keyboard_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    return window;
}

// Rendering loop
void RenderLoop(
        GLFWwindow* window,
        GLuint VAO,
        GLuint EBO,
        Shader& shader)
{
    World* the_world = World::GetPtr();
    Camera& the_camera = the_world->GetCamera();

    // render loop
    while(!glfwWindowShouldClose(window))
    {
        // Check if any input was received from the user
        // Set background color.
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Clear buffers from last render iteration, otherwise
        // it will be re-used.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update transformation matrix in shader
        glm::mat4 model = the_world->GetModelMatrix();
        glm::mat4 view  = the_camera.GetViewMatrix();
        shader.setMat4f("model", model);
        shader.setMat4f("view", view);
        shader.setVec3("viewPos_world", the_camera.GetPosition().glm());


        //glm::vec3 lightPos_world( 0.0, light_radius*glm::cos(glm::radians(light_angle)), light_radius*glm::sin(glm::radians(light_angle)) );
        glm::vec3 lightPos_world = the_camera.GetPosition().glm();
        shader.setVec3("lightPos_world", lightPos_world);
        light_angle += 1;

        // Draw elements
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        GLsizei elem_array_size = World::GetPtr()->ElementCount() * 3;
        void* offset = 0;
        glDrawElements(GL_TRIANGLES, elem_array_size, GL_UNSIGNED_INT, offset);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch(key)
        {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, true);
                break;
            case GLFW_KEY_UP:
                World::GetPtr()->Rotate(0.5, Vect3f(1.0, 0.0, 0.0));
                break;
            case GLFW_KEY_DOWN:
                World::GetPtr()->Rotate(-0.5, Vect3f(1.0, 0.0, 0.0));
                break;
            case GLFW_KEY_LEFT:
                World::GetPtr()->Rotate(0.5, Vect3f(0.0, 1.0, 0.0));
                break;
            case GLFW_KEY_RIGHT:
                World::GetPtr()->Rotate(-0.5, Vect3f(0.0, 1.0, 0.0));
                break;
            case GLFW_KEY_A:
                World::GetPtr()->GetCamera().Translate(Vect3f(0.0f, 0.0f, 0.1f));
                break;
            case GLFW_KEY_S:
                World::GetPtr()->GetCamera().Translate(Vect3f(0.0f, 0.0f, -0.1f));
                break;
            case GLFW_KEY_D:
                World::GetPtr()->GetCamera().Translate(Vect3f(-0.1f, 0.0f, 0.0f));
                break;
            case GLFW_KEY_F:
                World::GetPtr()->GetCamera().Translate(Vect3f(0.1f, 0.0f, 0.0f));
                break;
            case GLFW_KEY_R:
                World::GetPtr()->GetCamera().Reset();
                break;
        };
    };
};

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    std::cout << "Mouse x:" << xpos << " y:" << ypos << std::endl;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        switch(button)
        {
            case GLFW_MOUSE_BUTTON_RIGHT:
            std::cout << "Right button press" << std::endl;
            break;
            case GLFW_MOUSE_BUTTON_LEFT:
            std::cout << "Left button press" << std::endl;
            break;
        };
    }
    else if(action == GLFW_RELEASE)
    {
        switch(button)
        {
            case GLFW_MOUSE_BUTTON_RIGHT:
            std::cout << "Right button release" << std::endl;
            break;
            case GLFW_MOUSE_BUTTON_LEFT:
            std::cout << "Left button release" << std::endl;
            break;
        };
    }
};

// Callback : When window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Resize OpenGL viewport to match window size
    glViewport(0, 0, width, height);
}


// Process command line options
CommandLineOptions ProcessCommandLineOptions(int argc, char** argv)
{
    CommandLineOptions options;
    for(int i=0; i < argc; ++i)
    {
        std::string arg(argv[i]);
        if(arg.compare("--wireframe") == 0)
        {
            options.wireframeMode = true;
        }
    }
    return options;
}
