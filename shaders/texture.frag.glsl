#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;
uniform bool hasTexture;

// texture samplers
uniform sampler2D texture_quad;

void main()
{
    FragColor = texture(texture_quad, TexCoord);
}