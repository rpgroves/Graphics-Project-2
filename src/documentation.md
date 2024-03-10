# Brody Foster, Ryan Groves, HW2 Documentation

## 1. Objects

### .obj Files
Our VBO and VAO data are determined be reading data from a .obj file. .obj files have the following properties that we utilize: vertices and faces. Vertices are read using lines that start with "v " and faces from lines that start with "f ". Vertex data gives us each vertex in order and their positions, and faces tell us which vertices are part of each face. We use this data to create a separate triangles data structure.

### Separate Triangles Data Structure
This data structure is created by treating the vertices of each face as separate from the vertices of any other face. Essentially this means that is a vertex is part of more than one face, then its data is stored more than once, once for each face. We use the face data to determine which vertices that we found must have their data used by this face (ie. vertices 1, 2, and 4). The vertices are put into the VBO in this order.

### VBO and VAO
The VBO and VAO help us build up the vertex data in a simple container. Our VBO contains 3 floats for location, then 3 floats for color for each vertex, and contains every used vertex in order of how they appear on faces. For instance if face 1 had vertices 1, 2, 4 and face 2 had vertices 1, 3, 4, then the VBO would contain vertices in the following order 1, 2, 4, 1, 3, 4. Notice that vertices 1 and 4 are duplicated as they appear in multiple faces, this is because of our separate triangles data structure.

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