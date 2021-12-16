#version 330 core
in vec4 ourColor;
out vec4 FragColor;  

//uniform int scelta;
 uniform float time;
 uniform vec2 resolution;
int scelta=1;
#define pi 3.14159235659
void main()
{
    if (scelta==1)
    {
        FragColor = vec4(ourColor);
    }
    if (scelta==0)
    {
	 vec2 uv = gl_FragCoord.xy / resolution; 
	float forma = (sin(uv.x*200.*pi)*0.5+0.5)*(sin(uv.y*10.*pi)*0.5+0.5);
	float forma2 = uv.y;
	float forma3 = uv.y;
	float r = forma;
	float g = forma ;
	float b = forma3;
		
	FragColor = vec4 (r,g,b,1.0);  
    }   
     if (scelta==2)
    {
   
    vec2 uv = gl_FragCoord.xy / resolution; 
	
	float forma = (sin(uv.x*20.*pi-time)*0.5+0.5)*(sin(uv.y*10.*pi+time)*0.5+0.5);
	float forma2 = uv.y;
	float forma3 = uv.y;
	float r = forma;
	float g = forma2;
	float b = forma3;
		
	FragColor = vec4 (r,g,b,1.0);  
    } 

     if (scelta==3)
    {
   
    vec2 uv = gl_FragCoord.xy / resolution; 
	
	float forma = (sin(uv.x*15.*pi-time)*0.5+0.5)*(sin(uv.y*15.*pi+time)*0.5+0.5);
	float forma2 = uv.y;
	float forma3 = sqrt(uv.y);
	float r = forma;
	float g = forma2;
	float b = forma3;
		
	FragColor = vec4 (r,g,b,1.0);  
    } 
}