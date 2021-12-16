#ifndef SHADER_MAKER_H
#define SHADER_MAKER_H
#include "Lib.h"

class ShaderMaker
{
    public:
		static GLuint createProgram(char* vertexfilename, char *fragmentfilename);
		static char* readShaderSource(const char* shaderFile);
	
    private:
		ShaderMaker() { }	
};

#endif