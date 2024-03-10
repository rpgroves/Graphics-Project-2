
Resources:
https://learnopengl.com/Getting-started/Shaders


DONE:
- Added a vertexColor in/out variable to the frag/vert shader.
- Copied shader_s.h from learnOpenGL, Andrew K said their version is **far too much**, we can make our own stripped down version that doesn't implement <glad.h> or whatever

TODO:

- [x] Read vertex geometry and connectivity from .obj files to generate a "separate triangles" data structure in the `verticies` array.
    - [x] Try on a simple file first
        - [x] Modify data/cube.obj to have triangular faces rather than quad faces
            - [x] Learn how wavefronts work :( https://en.wikipedia.org/wiki/Wavefront_.obj_file

- [x] Allow VBOs and VAOs to asssign a color to each vertex.
    - [ ] Modify the vertex/fragment shaders to render based on said color.

- [x] Read in shader code from a separate file rather than a hardcoded const string.

- [ ] Construct a *Model Viewmatrix* for placing an object in a scene.
    - [ ] GLM provides certain matricies to use for composition...
    - [ ] Implement **TWO** methods to later compare:
        - [ ] Transform the geometry and then send the transformed coordinates to GPU for rendering 
        - [ ] Sending the transformation matrix to GPU to apply to geometry during rendering. 

- [ ] Allow users to interact with the transform with simple input

- [ ] *Bonus*: Read about the Element Buffer Objects (EBOs) to implement the “indexed triangle” data structure that we learned in class. +10pts
    How do we specifically implement indexed triangles?


- [ ] REPORT
    - [ ] Documents each implemented functionality
    - [ ] Compares performance of each approach on large meshes.