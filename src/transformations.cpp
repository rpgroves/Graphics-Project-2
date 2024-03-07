#include <glm/glm.hpp>
#include <glm/ext.hpp> // ?

glm::mat4 model         = glm::mat4(1.0f); // local space           -> world space
glm::mat4 view          = glm::mat4(1.0f); // model (world) space   -> view space 
glm::mat4 projection    = glm::mat4(1.0f); // view space            -> clip space

// orthographic projection with a bounding box of 800x600, bottom left corner at (0,0), near plane at 0.1, far plane at 100.0
glm::mat4 orthographic = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

// perspective projection with a 45 degree field of view, a 4:3 aspect ratio, near plane at 0.1, far plane at 100.0
glm::mat4 proj = glm::perspective(glm::radians(45.0f), 4.0f/3.0f, 0.1f, 100.0f);



// eventually.. if we want to pass the transformation matrices to the shader as uniforms, we can do this:
//gl_Position = projection * view * model * vec4(aPos, 1.0);