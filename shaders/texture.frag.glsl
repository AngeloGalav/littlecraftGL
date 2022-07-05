#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture_quad;

void main()
{
    FragColor = texture(texture_quad, TexCoord);
}