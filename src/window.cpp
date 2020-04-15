#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <exception>

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLuint setupShaderProgram();

const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "out vec4 vertexColor;\n"
                                 "void main()\n"
                                 "{\n"
                                 "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
                                 "}\n\0";
                    

const char* fragmentShaderSource = "#version 330 core\n"
                                   "in vec4 vertexColor;\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vertexColor;\n"
                                   "}\n\0";


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

    // Compile vertex shader, fragment shader and link to a program
    GLuint shaderProgram = setupShaderProgram();

    // Set up vertex data
    float vertices[] = {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
       -0.5f,  0.5f, 0.0f
    };

    // Triangle indices
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    GLuint vertex_attribute_id = 0;   // I think this has been hardcoded in the shader
    GLuint num_comp = 3;              // 3 co-ordinates per vertex
    GLsizei stride = 3*sizeof(float); // Stride size
    void* start_offset = NULL;        // Offset from start
    glVertexAttribPointer(vertex_attribute_id, num_comp, GL_FLOAT, GL_FALSE, stride, start_offset);
    glEnableVertexAttribArray(vertex_attribute_id);

    /* Create an element buffer object (EBO)
     */
     GLuint EBO;
     glGenBuffers(1, &EBO);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // render loop
    while(!glfwWindowShouldClose(window))
    {
        // Check if any input was received from the user
        processInput(window);

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw elements
        glUseProgram(shaderProgram);
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

// Compiles vertex and fragment shaders and links them into a shader program.
// Returns handle to the shader program if successful, exits if unsuccessul.
GLuint setupShaderProgram()
{
    int success;
    char infoLog[512];

    // Compile vertex shader program
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &(vertexShaderSource), NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Vertex shader compilation failed :\n" << infoLog << std::endl;
    }
    else
    {
        std::cout << "Vertex shader compiled successfully" << std::endl;
    }

    // Compile fragment shader program
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &(fragmentShaderSource), NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Fragment shader compilation failed :\n" << infoLog << std::endl;
        std::terminate();
    }
    else
    {
        std::cout << "Fragment shader compiled successfully" << std::endl;
    }

    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Shader program linking failed :\n" << infoLog << std::endl;
        std::terminate();
    }
    else
    {
        std::cout << "Shader program linked successfully" << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
