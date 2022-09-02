#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec4 aColor; // the color variable has attribute position 1
layout (location = 2) in vec2 textureCoords;  

uniform mat4 Model;
uniform mat4 Projection;
uniform mat4 View;
out vec4 ourColor; // output a color to the fragment shader
out vec2 TexCoord;
out vec3 view_pos;

void main()
{
    gl_Position = Projection*View*Model*vec4(aPos, 1.0);
    ourColor = aColor; // set ourColor to the input color we got from the vertex data
    TexCoord = vec2(textureCoords.x, textureCoords.y); // inviamo al fragment le coordinate della texture 
    
    // usato per la nebbia
    view_pos = ((View * Model) * vec4(aPos, 1.0)).xyz;
}  

