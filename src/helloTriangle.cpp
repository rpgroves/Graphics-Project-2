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

    // Loading shaders from file.
    Shader loadedShader("src/shaders/matrixUniformVertex.shader", "src/shaders/basicFragment.fs");
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------


//This section added / changed by Riley :3 essentially you just need to change the loadedFile to change what vertices are loaded in
//This section currently ignored all obj file lines except those with vertices
///////////////////////////////////////////////////////////////////////////////////////////////////

    int vertexAttributeCount = 6;

    string loadedFile = "cube.obj";
    string filePath = "data/" + loadedFile;

    ifstream myfile;
    myfile.open (filePath);

    vector<float> objData;
    vector<int> vertexOrder;

    bool colorSwap = true;
    for(string line; getline(myfile, line);)
    {
        string lineTemp = line;
        if(line != "" && line.at(0) == 'v' && line.at(1) == ' ')
        {
            lineTemp = lineTemp.substr(2);
            objData.push_back(stof(lineTemp.substr(0, lineTemp.find(' '))));
            lineTemp = lineTemp.substr(lineTemp.find(' ') + 1);
            objData.push_back(stof(lineTemp.substr(0, lineTemp.find(' '))));
            lineTemp = lineTemp.substr(lineTemp.find(' ') + 1);
            objData.push_back(stof(lineTemp.substr(0)));


            float color = 0.5;
            if(colorSwap)
                color = 1.0f;
            colorSwap = !colorSwap;
            objData.push_back(color);
            objData.push_back(0.0f);
            objData.push_back(color);
        }
        if(line != "" && line.at(0) == 'f' && line.at(1) == ' ')
        {
            lineTemp = lineTemp.substr(2);
            string numTemp = "";
            for(long unsigned int i = 0; i < lineTemp.size(); i++)
            {
                if(lineTemp.at(i) == '/')
                {
                    vertexOrder.push_back(stoi(numTemp));
                    numTemp = "";
                    i++;
                }
                else if(lineTemp.at(i) != ' ')
                {
                    numTemp += lineTemp.at(i);
                }
                else
                    numTemp = "";
            }
        }
    }
        
    float vertices[vertexOrder.size() * vertexAttributeCount];
    int verticesIndex = 0;
    for(long unsigned int i = 0; i < vertexOrder.size(); i++)
    {
        int vertexToAdd = vertexOrder.at(i) - 1;

        for(int j = 0; j < vertexAttributeCount; j++)
        {
            vertices[verticesIndex] = objData.at(vertexToAdd * vertexAttributeCount + j);
            cout << vertices[verticesIndex] << " ";
            verticesIndex++;
        }
        cout << endl;
    }
    unsigned int numVertices = vertexOrder.size();

    //To see the colorful triangle, uncomment what is below and comment what is above (up to the bar ///)

    // float vertices[] = {
    //     0.5f, -0.5f, 0.0f,      1.0f, 0.0f, 0.0f,
    //     -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
    //     0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f
    // };
    // unsigned int numVertices = sizeof(vertices)/vertexAttributeCount;
///////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //Vertex Attribute Pointers:
    //When you add a new field, increment parameter 4 (the size of) in every line that has the pointer, ie when
    //color got added it went from 3 to 6 because of 3 new floats. Also for each new attribute pointer line increment the
    //first parameter based on which attirbute number you are working with (color comes second so its index 1), also do this for the enablevertexattribarray line

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexAttributeCount * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexAttributeCount * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


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
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        //glUseProgram(shaderProgram); replacing this with custom shader renderer
        loadedShader.use();
        // set uniforms here!
        glm::mat4 model         = glm::mat4(1.0f);
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);

        //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        
        loadedShader.setMat4("model", model);
        loadedShader.setMat4("view", view);
        loadedShader.setMat4("projection", projection);
        
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, numVertices);
        // glBindVertexArray(0); // unbind our VA no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
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