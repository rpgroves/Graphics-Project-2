# Sorry this is late again haha

## Setup
Makefile assumes installation of GLEW/GLFW3, glm is included in the files.

The program is built to build/modelViewer.exe

Run `make` in the same directory as the make file to build. (Run `make clean` if build/ already exists.)

Then, run `./build/modelViewer.exe`.


## CONFIGURATIONS
There are 3 variables in `main.cpp` that you can edit to alter the program. 
- The default directory for an obj file.
- Screen width/height
- A boolean that defers transformation from the CPU to the GPU.\


## CONTROLS
The program has a few keyboard controls to manipulate the model view.

SHIFT/ENTER to zoom in/out.
WASD to translate.
Arrow keys to rotate.