#include <glm/glm.hpp>
#include <glm/ext.hpp> // ?


// each object needs to undergo the following transformation pipeline
// Local space,     - Defined in the obj file itself. 0,0,0 is the object origin
// -> World space   - Defined by the position of the object in the world. 0,0,0 is the world origin 
//                           (need a position uniform? or something?)
// -> View space    - Defined by camera properties. 0,0,0 is the camera position.
// -> Clip space    - This is what we want to have in our VBO's. Except maybe some W division beforehand?? idk
//  
// GPU does then takes care of:
// -> Normalized device coordinates -> Screen space

glm::mat4 model         = glm::mat4(1.0f); // local space           -> world space
glm::mat4 view          = glm::mat4(1.0f); // model (world) space   -> view space 
glm::mat4 projection    = glm::mat4(1.0f); // view space            -> clip space

// orthographic projection with a bounding box of 800x600, bottom left corner at (0,0), near plane at 0.1, far plane at 100.0
glm::mat4 orthographic = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

// perspective projection with a 45 degree field of view, a 4:3 aspect ratio, near plane at 0.1, far plane at 100.0
glm::mat4 proj = glm::perspective(glm::radians(45.0f), 4.0f/3.0f, 0.1f, 100.0f);



// eventually.. if we want to pass the transformation matrices to the shader as uniforms, we can do this:
//gl_Position = projection * view * model * vec4(aPos, 1.0);