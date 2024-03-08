#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0

out vec3 vertexColor; // specify a color output to the fragment shader

void main() {
    vertexColor = vec3(0.5, 0.0, 0.0); // set the output variable to a dark-red color

    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}