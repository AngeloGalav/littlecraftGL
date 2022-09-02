#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;
in vec3 view_pos;

// texture samplers
uniform sampler2D texture_quad;

const vec4 fog_color = vec4(0.5, 0.8, 0.9, 1.0);
const float fog_near = 50;
const float fog_far = 70;


void main()
{
    FragColor = texture(texture_quad, TexCoord);
    
    float fog = smoothstep(fog_near, fog_far, length(view_pos));
    FragColor = mix(FragColor, fog_color, fog);
}