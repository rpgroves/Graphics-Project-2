// template based on material from learnopengl.com
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "shader_s.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glm/ext.hpp>

#include "gl_debug_tool.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "viewGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // // glew: load all OpenGL function pointers
    glewInit();
    
    // Configure global OpenGL state
    glEnable(GL_DEPTH_TEST);
    
    // ------------------------------------------------------------------

    // Loading shaders from file.
    Shader loadedShader("src/shaders/matrixUniformVertex.vs", "src/shaders/basicFragment.fs");

    // Set up vertex data (many attributes, including position and color, in one array)
    // ------------------------------------------------------------------
       float vertices[] = {
        /*  
        // positions            // colors
         0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,  // bottom right     // VERTEX ONE
        -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,  // bottom left      // VERTEX TWO
         0.0f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f   // top              // VERTEX THREE
         */
        // Faces of cubes,      // Colors are arbitrary bc these were UV coordinates before, I just appended 0.0f to the end of each line.
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
        
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,

         0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f
        
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,
        1, 2, 3
    };  
    // WHY are the indices like this!! None of this makes sense.

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // Set up VBO, VAO, EBOs
    // ------------------------------------------------------------------
    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    // 1. Copy vertices array into a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 2. Then set the vertex attributes pointers
        // This line is the most important line in this program. It tells OpenGL how to interpret all of our data.
        // The first parameter specifies which vertex attribute we want to configure. (We have two, position and color).
        // The secod parameter specifies the size of the vertex attribute. (Position and color are both 3D vectors, so it is composed of 3 floats).
        // The third parameter specifies the type of the data. The data is of type GL_FLOAT.
        // The fifth parameter is the stride: the space between consecutive vertex attribute sets. 
        // The last parameter is the offset of where the position data begins in the buffer.
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); 
    glEnableVertexAttribArray(0);
    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 3. Copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // NOTE: The last element buffer object that gets bound while a VAO is bound, is stored as the VAO's element buffer object.
    //       Binding to a VAO then also automatically binds that EBO. 


    // Reset the buffer and array bindings
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);  // NOTE: You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    //                      VAOs requires a call to glBindVertexArray anyways, so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.


    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // when the heck did the depth buffer get here? what's with the | operator?
        // TODO: not sure where to call shader.use().

        // set uniforms here!
       
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);

        //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f)); // Camera is 10 feet back (forward..?) from the origin.
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        
        loadedShader.setMat4("view", view);
        loadedShader.setMat4("projection", projection);
        loadedShader.use();

        // Render our boxes!
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++) {

            // Calculate the model matrix for each object, which will be different for each object (translation).
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle) + (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
            loadedShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
            //glDrawElements(GL_TRIANGLES, 1, GL_UNSIGNED_INT, 0);
        }
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBindVertexArray(0);
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    //glDeleteProgram(shaderProgram); // no need to delete the shader program, it's deleted when the Shader object is destroyed.

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}