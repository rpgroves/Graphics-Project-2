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
#include "mesh.h"

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

    // Create a mesh
    std::vector<Vertex> vertices = { // bullshit normals and colors...
        {glm::vec3(0.5f,  0.5f, 0.0f),     glm::vec3(0.0f, 0.0f, 1.0f),    glm::vec3(1.0f, 0.0f, 0.0f)},
        {glm::vec3(0.5f, -0.5f, 0.0f),     glm::vec3(0.0f, 0.0f, 1.0f),    glm::vec3(1.0f, 0.0f, 0.0f)},
        {glm::vec3(-0.5f, -0.5f, 0.0f),    glm::vec3(0.0f, 0.0f, 1.0f),    glm::vec3(1.0f, 0.0f, 0.0f)},
        {glm::vec3(-0.5f, 0.5f, 0.0f),     glm::vec3(0.0f, 0.0f, 1.0f),    glm::vec3(1.0f, 0.0f, 0.0f)},
        
    };
    std::vector<unsigned int> indices = {
        0, 1, 3,
        1, 2, 3

    };


    Mesh myMesh(vertices, indices);
    // ------------------------------------------------------------------


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
        
        // Okay I read you call use() on the shader object BEFORE setting uniforms.
        loadedShader.use();
        
        glm::mat4 model         = glm::mat4(1.0f);
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);

        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f)); // Camera is 5 units back (forward..?) from the origin.
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        
        loadedShader.setMat4("view", view);
        loadedShader.setMat4("projection", projection);
        loadedShader.setMat4("model", model);


        myMesh.Draw(loadedShader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


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