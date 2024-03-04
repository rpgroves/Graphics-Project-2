
Resources:
https://learnopengl.com/Getting-started/Shaders


TODO:

- [ ] Allow VBOs and VAOs to asssign a color to each vertex.
    - [ ] Modify the vertex/fragment shaders to render based on said color.

- [ ] Read in shader code from a separate file rather than a hardcoded const string.

- [ ] Construct a *Model Viewmatrix* for placing an object in a scene.
    - [ ] GLM provides certain matricies to use for composition...
    - [ ] Implement **TWO** methods to later compare:
        - [ ] Transform the geometry and then send the transformed coordinates to GPU for rendering 
        - [ ] Sending the transformation matrix to GPU to apply to geometry during rendering. 

- [ ] Allow users to interact with the transform with simple input

- [ ] *Bonus*: Read about the Element Buffer Objects (EBOs) to implement the “indexed triangle”data structure that we learned in class.+10pts


- [ ] REPORT
    - [ ] Documents each implemented functionality
    - [ ] Compares performance of each approach on large meshes.