#version 330 core
in vec4 ourColor;
out vec4 FragColor;  

uniform int remove_mode;

void main()
{
	if (remove_mode == 0) {
		FragColor = ourColor;
	} else {
		FragColor = vec4(1.0, 0.0, 0.0, 0.5);
	}
}