# Brody Foster, Ryan Groves, HW2 Documentation

## 1. Objects

### .obj Files

### Separate Triangles Data Structure

### VBO and VAO

## 2. Shaders

### Vertex Shaders
Our vertex shaders consist of the following: colorVertex and basicVertex, both take in a position and color that consist of 3 floats each, and outputs a vec4 vertexColor. In main, both set gl_Position to be equal to the input position with one extra float on the end of value 1.0. This means that gl_Position contains a vec4 instead of the input vec3. BasicVertex sets the color to be consistent accross all vertices, while colorVertex sets the color to be equal to the input color value.

### Fragment Shaders
Our fragment shaders consist of only one shader currently, that being basicFragment.fs. This shader takes in a vec4 color and in main sets its output (vec4 FragColor) to be equal to the input.

### Vertex and Fragment Shader Files (.vs and .fs)
Our program is able to use separate .vs and .fs files to create and manage our shaders. Shaders are loaded within our helloTriangle.cpp file. Both shaders are loaded at once using the line Shader loadedShader("file1.vs", "file2.fs"); Then in the main loop we make sure to use our shader instead of the default shader by replacing glUseProgram(ShaderProgram) with loadedShader.use(). 

## 3. Transformations

### Object to Camera Space Transformation

### Linear Transformations

### Model View Matrix

###


**bold**
*italic*